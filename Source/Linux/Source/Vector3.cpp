#include <Vector3.hpp>

namespace Raster
{
	Vector3::Vector3( )
	{
	}

	Vector3::Vector3( const RAS_FLOAT32 p_X, const RAS_FLOAT32 p_Y,
		const RAS_FLOAT32 p_Z )
	{
	}

	Vector3::~Vector3( )
	{
	}

	void Vector3::Set( const Vector3 &p_Other )
	{
	}

	void Vector3::Set( const RAS_FLOAT32 p_X, const RAS_FLOAT32 p_Y,
		const RAS_FLOAT32 p_Z )
	{
	}

	RAS_FLOAT32 Vector3::GetMagnitude( ) const
	{
		return 1.0f;
	}

	RAS_FLOAT32 Vector3::GetMagnitudeSquare( ) const
	{
		return 1.0f;
	}

	RAS_FLOAT32 Vector3::GetDistance( const Vector3 &p_Other ) const
	{
		return 1.0f;
	}

	RAS_FLOAT32 Vector3::GetDistanceSquare( const Vector3 &p_Other ) const
	{
		return 1.0f;
	}

	void Vector3::Zero( )
	{
	}

	void Vector3::Clean( )
	{
	}

	void Vector3::Normalise( )
	{
	}

	RAS_FLOAT32 Vector3::Dot( const Vector3 &p_Other ) const
	{
		return 1.0f;
	}

	Vector3 Vector3::Cross( const Vector3 &p_Other ) const
	{
		Vector3 Cross;

		return Cross;
	}

	Vector3 Vector3::operator+( const Vector3 &p_Other ) const
	{
		Vector3 Add;

		return Add;
	}

	Vector3 Vector3::operator-( const Vector3 &p_Other ) const
	{
		Vector3 Subtract;

		return Subtract;
	}

	Vector3 Vector3::operator*( const Vector3 &p_Other ) const
	{
		Vector3 Multiply;

		return Multiply;
	}

	Vector3 Vector3::operator*( const RAS_FLOAT32 p_Scalar ) const
	{
		Vector3 Multiply;

		return Multiply;
	}

	Vector3 Vector3::operator/( const Vector3 &p_Other ) const
	{
		Vector3 Divide;

		return Divide;
	}

	Vector3 Vector3::operator/( const RAS_FLOAT32 p_Scalar ) const
	{
		Vector3 Divide;

		return Divide;
	}

	Vector3 &Vector3::operator+=( const Vector3 &p_Other )
	{
		return *this;
	}

	Vector3 &Vector3::operator-=( const Vector3 &p_Other )
	{
		return *this;
	}

	Vector3 &Vector3::operator*=( const Vector3 &p_Other )
	{
		return *this;
	}

	Vector3 &Vector3::operator*=( const RAS_FLOAT32 p_Scalar )
	{
		return *this;
	}

	Vector3 &Vector3::operator/=( const Vector3 &p_Other )
	{
		return *this;
	}

	Vector3 &Vector3::operator/=( const RAS_FLOAT32 p_Other )
	{
		return *this;
	}
}

