#ifndef INCLUDED_STRINGRENDERER_H
#define INCLUDED_STRINGRENDERER_H

class Image;



class StringRenderer{
public:
	static StringRenderer* instance();

	void draw( int x, int y, const char* string ) const;
	void draw( int x, int y, const char* string, int size );
	static void create( const char* fontFileName );
	static void destroy();	
private:
	StringRenderer( const char* fontFileName );
	~StringRenderer();

	Image* mImage;
	static StringRenderer* mInstance;
};
#endif