#!/bin/bash

if [ -d "$HOME/.local/share/popcat" ]; then
    rm -rf "$HOME/.local/share/popcat"    
fi

mkdir -p ~/.local/share/popcat

# Copy files
cp popcat ~/.local/share/popcat/
cp popcat.png ~/.local/share/popcat/

# Create .desktop file
cat << EOF > ~/.local/share/applications/popcat.desktop
[Desktop Entry]
Version=1.0
Type=Application
Name=popcat
Comment=Make popcat pop!
Exec=$HOME/.local/share/popcat/popcat
Icon=$HOME/.local/share/popcat/popcat.png
Terminal=false
Categories=Utility;
EOF

# Make it executable
chmod +x ~/.local/share/applications/popcat.desktop

update-desktop-database ~/.local/share/applications

echo "Installed! Search 'Popcat' in your app launcher."
