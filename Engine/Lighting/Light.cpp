#include "Light.h"

Light::Light () :
	_color (Color::White),
	_specularColor (Color::White)
{
	_rigidbody->SetGravityUse (0);
}

Light::~Light ()
{

}

Color Light::GetColor () const
{
	return _color;
}

Color Light::GetSpecularColor () const
{
	return _specularColor;
}

void Light::SetColor (const Color& color)
{
	_color = color;
}

void Light::SetSpecularColor (const Color& specularColor)
{
	_specularColor = specularColor;
}