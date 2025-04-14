#!/bin/bash

echo "Uninstalling Popcat..."

# Remove app directory
if [ -d "$HOME/.local/share/popcat" ]; then
    rm -rf "$HOME/.local/share/popcat"    
fi

# Remove .desktop launcher
rm -f "$HOME/.local/share/applications/popcat.desktop"

# Update desktop database
update-desktop-database "$HOME/.local/share/applications"

echo "Popcat has been uninstalled!"
