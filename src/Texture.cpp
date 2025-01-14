/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//----------------------------------------------------------------------------------------------------------------------
/// @file Texture.cpp
/// @brief implementation files for Texture class
//----------------------------------------------------------------------------------------------------------------------
#include "NGLassert.h"
#include "Texture.h"
#include <iostream>

namespace ngl
{


//----------------------------------------------------------------------------------------------------------------------
Texture::Texture()
{
	m_width=0;
	m_height=0;
	m_multiTextureID=0;
	m_hasAlpha=false;
	m_channels=0;
	m_format=0;
}

//----------------------------------------------------------------------------------------------------------------------
Texture::Texture( const std::string &_fname  )
{
	m_image.load(_fname);
	m_width=m_image.width();
	m_height=m_image.height();
	m_channels=m_image.channels();
	m_format=m_image.format();
	m_multiTextureID=0;
}


bool Texture::loadImage( const std::string  &_fname )
{
	return m_image.load(_fname);
}

//----------------------------------------------------------------------------------------------------------------------
Texture::~Texture()
{
	// smart pointer in image clears for us
}


//----------------------------------------------------------------------------------------------------------------------

/// @note this is really inflexible at the moment needs to be made more generic and give more
/// control over the OpenGL texture types etc
/// Could actually be worth creating a texture manager class at some stage along the lines of the
/// Shader manager class, or even a generic manager framework which we could then add items to

GLuint Texture::setTextureGL() const
{
  GLuint textureName;
  glGenTextures(1,&textureName);
  glActiveTexture(GL_TEXTURE0+m_multiTextureID);
  glBindTexture(GL_TEXTURE_2D,textureName);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D,0,m_format,m_width,m_height,0,m_format,GL_UNSIGNED_BYTE,m_image.getPixels());
  std::cout<<"texture GL set "<<textureName<<" Active Texture "<<m_multiTextureID<<"\n";
  glGenerateMipmap(GL_TEXTURE_2D);
  return textureName;
}
//----------------------------------------------------------------------------------------------------------------------

void Texture::setMultiTexture( const GLint _id  )
{
 m_multiTextureID=_id;
}



} // end namespace ngl;

//----------------------------------------------------------------------------------------------------------------------

