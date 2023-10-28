# Noku Player
## Layout

- Interface:
    - The visual aspect of the program.
    - An interface is made up of pages, which contain components.
    - The interface will have a nav bar.
    - InterfacePage:
        - Contains a surface for drawing.
        - Contains a function to turn the surface into a texture for drawing.
        - Can be scrolled through if necessary.
        - Can also be set to not scroll.
        - Belongs to interface.
        - Obtains window from interface.
        - InterfaceComponent:
            - An interactable component.
            - Contains an Update and Draw method.
            - Each component must handle it's own drawing and updating.
            - Each component will receive position data.
            - Components belong to a page, which will draw them to its surface.

- Song:
    - Song path.
    - Song metadata:
        - Song artist.
        - Song album.
        - Song copyright.

- Playlist (class):
    - Made up of PlaylistItems (struct)
        - Position in playlist.
        - Pointer to song object.