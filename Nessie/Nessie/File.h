#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

class File{
public:
	File( const char* filename );
	~File();
	unsigned getUnsigned( int position ) const;
private:
	int mSize;
	char* mData;
};

#endif