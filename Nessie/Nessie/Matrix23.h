#ifndef INCLUDED_MATRIX_23_H
#define INCLUDED_MATRIX_23_H

class Vector2;
class Matrix23{
public:
	Matrix23();
	void setTranslation( const Vector2& );
	void multiply( Vector2* out, const Vector2& in ) const;
	void operator*=( const Matrix23& );
	void translate( const Vector2& );
	void scale( const Vector2& );
private:
	double m00, m01, m02;
	double m10, m11, m12;
};

#endif