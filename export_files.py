#!/usr/bin/env python3
"""
Export all project files (excluding minilibx-linux and textures) to a JSON file.
"""

import os
import json
from pathlib import Path

# Directories and patterns to exclude
EXCLUDE_DIRS = {'minilibx-linux', 'textures', '.git', '__pycache__', '.vscode'}
EXCLUDE_EXTENSIONS = {'.o', '.a', '.so', '.xpm', '.png', '.jpg', '.jpeg', '.gif', '.bmp'}

def should_include(path: Path, root: Path) -> bool:
    """Check if a file should be included in the export."""
    # Check if any parent directory is in exclude list
    parts = path.relative_to(root).parts
    for part in parts:
        if part in EXCLUDE_DIRS:
            return False
    
    # Check extension
    if path.suffix.lower() in EXCLUDE_EXTENSIONS:
        return False
    
    # Skip binary/compiled files
    if path.name in {'cub3d', 'cub3d_bonus'}:
        return False
    
    return True

def read_file_content(filepath: Path) -> str:
    """Read file content, return None if binary or unreadable."""
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            return f.read()
    except (UnicodeDecodeError, PermissionError):
        return None

def export_files(root_dir: str, output_file: str = 'project_files.json'):
    """Export all project files to a JSON file."""
    root = Path(root_dir).resolve()
    files_data = {}
    
    for filepath in root.rglob('*'):
        if not filepath.is_file():
            continue
        
        if not should_include(filepath, root):
            continue
        
        content = read_file_content(filepath)
        if content is not None:
            relative_path = str(filepath.relative_to(root))
            files_data[relative_path] = content
            print(f"Added: {relative_path}")
    
    output_path = root / output_file
    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(files_data, f, indent=2, ensure_ascii=False)
    
    print(f"\n✅ Exported {len(files_data)} files to {output_path}")

if __name__ == '__main__':
    # Run from the script's directory
    script_dir = Path(__file__).parent.resolve()
    export_files(script_dir)
