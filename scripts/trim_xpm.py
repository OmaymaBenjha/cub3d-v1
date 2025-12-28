#!/usr/bin/env python3
"""
Script to trim transparent borders from XPM files.
Usage: python3 trim_xpm.py <input.xpm> [output.xpm] [padding]
If no output is specified, it overwrites the input file.
"""

import sys
import re

def parse_xpm(filepath):
    """Parse an XPM file and return its components."""
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Find all quoted strings in the file
    quoted_strings = re.findall(r'"([^"]*)"', content)
    
    if not quoted_strings:
        raise ValueError("No quoted strings found in XPM file")
    
    # First quoted string should be the header
    header = quoted_strings[0]
    header_match = re.match(r'(\d+)\s+(\d+)\s+(\d+)\s+(\d+)', header)
    
    if not header_match:
        raise ValueError(f"Could not parse XPM header: {header[:50]}")
    
    width = int(header_match.group(1))
    height = int(header_match.group(2))
    num_colors = int(header_match.group(3))
    cpp = int(header_match.group(4))
    
    print(f"Original: {width}x{height}, {num_colors} colors, {cpp} chars per pixel")
    
    # Color definitions are the next num_colors strings
    color_lines = quoted_strings[1:1+num_colors]
    
    # Find transparent color symbol
    transparent_symbol = None
    for cl in color_lines:
        if 'None' in cl or 'none' in cl:
            # The symbol is the first cpp characters
            transparent_symbol = cl[:cpp]
            break
    
    if transparent_symbol is None:
        print("Warning: No transparent color found, using space")
        transparent_symbol = ' ' * cpp
    
    print(f"Transparent symbol: repr='{repr(transparent_symbol)}'")
    
    # Pixel data are the remaining strings (should be height lines)
    pixel_lines = quoted_strings[1+num_colors:1+num_colors+height]
    
    if len(pixel_lines) != height:
        print(f"Warning: Expected {height} pixel lines, got {len(pixel_lines)}")
    
    # Get everything before the first quoted string for header preservation
    first_quote = content.find('"')
    lines_before = content[:first_quote].rstrip()
    
    return {
        'lines_before': lines_before,
        'width': width,
        'height': height,
        'num_colors': num_colors,
        'cpp': cpp,
        'color_lines': color_lines,
        'pixel_lines': pixel_lines,
        'transparent_symbol': transparent_symbol
    }


def find_bounds(pixel_lines, transparent_symbol, cpp):
    """Find the bounding box of non-transparent pixels."""
    top, bottom, left, right = None, None, None, None
    
    for row_idx, row in enumerate(pixel_lines):
        # Check each pixel in the row
        for col_idx in range(0, len(row), cpp):
            pixel = row[col_idx:col_idx + cpp]
            if pixel != transparent_symbol:
                if top is None:
                    top = row_idx
                bottom = row_idx
                pixel_col = col_idx // cpp
                if left is None or pixel_col < left:
                    left = pixel_col
                if right is None or pixel_col > right:
                    right = pixel_col
    
    if top is None:
        return None  # Entire image is transparent
    
    return (top, bottom, left, right)


def trim_xpm(parsed, bounds, padding=0):
    """Trim the XPM to the bounding box plus optional padding."""
    top, bottom, left, right = bounds
    cpp = parsed['cpp']
    
    # Add padding
    top = max(0, top - padding)
    bottom = min(len(parsed['pixel_lines']) - 1, bottom + padding)
    left = max(0, left - padding)
    right = min(parsed['width'] - 1, right + padding)
    
    new_width = right - left + 1
    new_height = bottom - top + 1
    
    print(f"Trimmed: {new_width}x{new_height}")
    print(f"Bounds: top={top}, bottom={bottom}, left={left}, right={right}")
    
    # Extract trimmed pixel data
    new_pixel_lines = []
    for row_idx in range(top, bottom + 1):
        row = parsed['pixel_lines'][row_idx]
        start_char = left * cpp
        end_char = (right + 1) * cpp
        new_row = row[start_char:end_char]
        new_pixel_lines.append(new_row)
    
    return {
        'width': new_width,
        'height': new_height,
        'num_colors': parsed['num_colors'],
        'cpp': parsed['cpp'],
        'color_lines': parsed['color_lines'],
        'pixel_lines': new_pixel_lines,
        'lines_before': parsed['lines_before']
    }


def write_xpm(output_path, data):
    """Write an XPM file."""
    with open(output_path, 'w') as f:
        # Write header
        f.write(data['lines_before'] + '\n')
        
        # Write dimension line
        f.write(f'"{data["width"]} {data["height"]} {data["num_colors"]} {data["cpp"]} ",\n')
        
        # Write color definitions
        for color_line in data['color_lines']:
            f.write(f'"{color_line}",\n')
        
        # Write pixel data
        f.write('/* pixels */\n')
        for i, pixel_line in enumerate(data['pixel_lines']):
            if i < len(data['pixel_lines']) - 1:
                f.write(f'"{pixel_line}",\n')
            else:
                f.write(f'"{pixel_line}"\n')
        
        f.write('};\n')


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 trim_xpm.py <input.xpm> [output.xpm] [padding]")
        print("  padding: optional number of pixels to keep around content (default: 0)")
        sys.exit(1)
    
    input_path = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) > 2 else input_path
    padding = int(sys.argv[3]) if len(sys.argv) > 3 else 0
    
    print(f"Processing: {input_path}")
    
    parsed = parse_xpm(input_path)
    bounds = find_bounds(parsed['pixel_lines'], parsed['transparent_symbol'], parsed['cpp'])
    
    if bounds is None:
        print("Error: Image is entirely transparent!")
        sys.exit(1)
    
    trimmed = trim_xpm(parsed, bounds, padding)
    write_xpm(output_path, trimmed)
    
    print(f"Saved to: {output_path}")
    print(f"Size reduced from {parsed['width']}x{parsed['height']} to {trimmed['width']}x{trimmed['height']}")


if __name__ == '__main__':
    main()
