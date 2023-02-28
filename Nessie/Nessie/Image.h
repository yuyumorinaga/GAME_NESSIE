#ifndef INCLUDED_IMAGE_H
#define INCLUDED_IMAGE_H

namespace GameLib{
    class Texture;
}
class Image{
public:
	Image( const char* filename );

	~Image();

	void draw(
	int dstX,
	int dstY,
	int srcX,
	int srcY,
	int width,
	int height ) const;

	void draw() const;

	void scalableDraw(
	int dstX,
	int dstY,
	int srcX,
	int srcY,
	int width,
	int height,
	int size ) ;

private:
	int mHeight;
	int mWidth;
	int mTextureWidth;
	int mTextureHeight;
	GameLib::Texture* mTexture;
};

#endif