//
// Created by Cindy Ngo on 8/3/20.
//
#pragma once
#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"

class TextureManager{
    static std::unordered_map< std::string, sf::Texture> textures;
    static void LoadTexture(const char *fileName);
public:
    static sf::Texture& GetTexture(const char *textureKey);
    static void Clear();
};
