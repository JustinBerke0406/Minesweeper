#include "ImageHelper.h"

#include <memory>

sf::Sprite ImageHelper::getSprite(const std::string &filename, int x1, int x2)
{
    sf::Texture& txt = getTexture(filename);

    sf::Sprite sprite(txt);

    // Select subsection of the texture
    if (x1 != -1) {
        if (x2 == -1)
            x2 = txt.getSize().x;

        sprite.setTextureRect(sf::IntRect(x1, 0, x2 - x1, txt.getSize().y));
    }

    return sprite;
}

sf::Texture* ImageHelper::getNewTexture(const std::string &filename)
{
    auto txt = new sf::Texture();

    txt->loadFromFile("images/" + filename);

    return txt;
}

sf::Sprite ImageHelper::getSprite(const std::string &filename, sf::Vector2f location, int x1, int x2)
{
    sf::Sprite sprite = getSprite(filename, x1, x2);

    sprite.setPosition(location);

    return sprite;
}

sf::Sprite* ImageHelper::getSpritePointer(const std::string &filename)
{
    auto* sprite = new sf::Sprite();

    sprite->setTexture(getTexture(filename));

    return sprite;
}

sf::Sprite* ImageHelper::getSpritePointer(const std::string &filename, sf::Vector2f location)
{
    auto* sprite = new sf::Sprite();

    sprite->setTexture(getTexture(filename));
    sprite->setPosition(location);

    return sprite;
}

ImageHelper::ImageHelper()
{
    // Fill map with all images
    dict["tile_hidden.png"] = getNewTexture("tile_hidden.png");
    dict["tile_revealed.png"] = getNewTexture("tile_revealed.png");
    dict["flag.png"] = getNewTexture("flag.png");
    dict["mine.png"] = getNewTexture("mine.png");
    dict["face_happy.png"] = getNewTexture("face_happy.png");
    dict["face_win.png"] = getNewTexture("face_win.png");
    dict["face_lose.png"] = getNewTexture("face_lose.png");
    dict["debug.png"] = getNewTexture("debug.png");
    dict["test_1.png"] = getNewTexture("test_1.png");
    dict["test_2.png"] = getNewTexture("test_2.png");
    dict["digits.png"] = getNewTexture("digits.png");

    for (int i = 1; i <= 8; i++)
        dict["number_" + std::to_string(i) + ".png"] = getNewTexture("number_" + std::to_string(i) + ".png");
}

sf::Texture& ImageHelper::getTexture(const std::string &filename)
{
    return *dict[filename];
}

ImageHelper::~ImageHelper()
{
    for (auto& text : dict)
        delete text.second;
}
