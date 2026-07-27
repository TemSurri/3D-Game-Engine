#include "texture.h"

void Tex::Create(const char* texFile) {

    if (ID != 0)
    {
        glDeleteTextures(1, &ID);
        ID = 0;
    }

    int widthT, heightT, numC;
    unsigned char* bytes = stbi_load(texFile, &widthT, &heightT, &numC, 4);

    if (!bytes)
    {
        return;
    }
    
    glGenTextures(1, &ID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);

    //adjust settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthT, heightT, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    //frees stbi data and unbinds texture
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void Tex::Bind() const {

    glBindTexture(GL_TEXTURE_2D, ID);

}

void Tex::UnBind() const{

    glBindTexture(GL_TEXTURE_2D, 0);

}