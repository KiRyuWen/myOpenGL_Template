
#include "./TextureBase.h"

#define STB_IMAGE_IMPLEMENTATION //define this !!!!
#include "./stb_image.h"

namespace OpenGLBase {
	
	TextureBase::TextureBase(const char* filePath, bool isMirrored)
	{
		//create id
		this->id = new GLuint;

		//load texture
		int n;
		stbi_uc* data = stbi_load(filePath, &this->width, &this->height, &n, 4);

		if (!data) //error
		{
			//Not found
			printf("Error texture loading, ");
			printf("Your path is:%s\n", filePath);
		}
		else //loaded ok
		{
			this->data = new unsigned char[this->width * this->height * 4 * sizeof(unsigned char)];
			memcpy(this->data, data, this->width * this->height * 4 * sizeof(unsigned char));

			if (isMirrored) {
				// vertical-mirror image data
				for (size_t i = 0; i < this->width; i++)
				{
					for (size_t j = 0; j < this->height / 2; j++)
					{
						for (size_t k = 0; k < 4; k++) {
							std::swap(this->data[(j * this->width + i) * 4 + k], this->data[((this->height - j - 1) * this->width + i) * 4 + k]);
						}
					}
				}
			}

			stbi_image_free(data);

			//generate texture
			this->GenerateTextures();
		}
	}
	void TextureBase::UseTexture()
	{
		if (this->id)
			glBindTexture(GL_TEXTURE_2D, *this->id);
		else
			std::cout << "Use texture error\n";
	}
	void TextureBase::BindTexture(GLenum bind_unit)
	{
		glActiveTexture(GL_TEXTURE0 + bind_unit);
		glBindTexture(GL_TEXTURE_2D, *this->id);
	}
}