#include "src/core/loaders/textureLoader/TextureLoader.hpp"

#include <SFML/Graphics/Texture.hpp>

const sf::Texture& TextureLoader::get(const char* filepath) {
    auto it = m_textures.find(filepath);
    if (it != m_textures.end()) {
        return *(it->second);
    }

    auto texture = std::make_unique<sf::Texture>();

    texture->setSmooth(m_isSmooth);
        
    if (!texture->loadFromFile(filepath)) {
        std::println("[TEXTURE LOADER] failed texture load : {}", filepath);
    }

    if (m_generateMipmaps) {
        if (texture->generateMipmap()) {
            std::println("[TEXTURE LOADER] Mipmaps generated for: {}", filepath);
            
            if (m_maxMipmapLevel > 0) {
                sf::Texture::bind(texture.get());
                
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, m_maxMipmapLevel);
                
                sf::Texture::bind(nullptr);
                std::println("[TEXTURE LOADER] Max mipmap level set to: {} for {}", m_maxMipmapLevel, filepath);
            }
        } else {
            std::println("[TEXTURE LOADER] WARNING: Failed to generate mipmaps for {}", filepath);
        }
    }

    std::println("[TEXTURE LOADER] texture load : {}", filepath);

    auto& textureRef = *texture;
    m_textures[filepath] = std::move(texture);
    return textureRef;
}