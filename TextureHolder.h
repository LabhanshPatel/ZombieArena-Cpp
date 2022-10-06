#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;

class TextureHolder {
private:
	std::map<std::string, Texture> m_Textures;
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static Texture& GetTexture(std::string const& filename);
};

#endif