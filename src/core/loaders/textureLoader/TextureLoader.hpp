#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <print>
#include <string>

class TextureLoader {
public:
    TextureLoader() = default;

    TextureLoader(const TextureLoader&) = delete;
    TextureLoader& operator=(const TextureLoader&) = delete;

    const sf::Texture& get(const std::string& filepath, int maxMipmapLevel = -1);

    void release(const std::string& filepath) { m_textures.erase(filepath); }

    void clear() { m_textures.clear(); }

    // SETTERS
    void setSmooth(bool smooth) { m_isSmooth = smooth; }
    void setGenerateMipmaps(bool generate) { m_generateMipmaps = generate; }
    void setMaxMipmapLevel(int level) { m_maxMipmapLevel = level; }

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;

    bool m_isSmooth{false};
    bool m_generateMipmaps{true};
    int m_maxMipmapLevel{4};
};
