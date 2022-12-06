#pragma once

#include <SFML/Graphics.hpp>

class ImageHelper
{
private:
    sf::Texture* getNewTexture(const std::string& filename);    // Creates new texture from the given file
    sf::Texture& getTexture(const std::string& filename);       // Returns a Texture from the map

    std::map<std::string, sf::Texture*> dict;
public:
    ImageHelper();

    sf::Sprite getSprite(const std::string& filename, int x1 = -1, int x2 = -1); // Get sprite based of the texture from the given file with the option to use a subsection of the texture
    sf::Sprite getSprite(const std::string& filename, sf::Vector2f location, int x1 = -1, int x2 = -1); // Get sprite based of the texture from the given file with the option to set a location and use a subsection of the texture

    sf::Sprite* getSpritePointer(const std::string& filename);  // Create a new sprite from a texture
    sf::Sprite* getSpritePointer(const std::string& filename, sf::Vector2f location); // Create a new sprite from a texture and set the location

    ~ImageHelper();
};