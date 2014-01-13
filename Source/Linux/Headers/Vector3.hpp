#ifndef __RASTER_VECTOR3_HPP__
#define __RASTER_VECTOR3_HPP__

#include <DataTypes.hpp>

namespace Raster
{
	class Vector3
	{
	public:
		Vector3( );
		Vector3( const RAS_FLOAT32 p_X, const RAS_FLOAT32 p_Y,
			const RAS_FLOAT32 p_Z );
		~Vector3( );

		void Set( const Vector3 &p_Other );
		void Set( const RAS_FLOAT32 p_X, const RAS_FLOAT32 p_Y,
			const RAS_FLOAT32 p_Z );

		RAS_FLOAT32 GetMagnitude( ) const;
		RAS_FLOAT32 GetMagnitudeSquare( ) const;

		RAS_FLOAT32 GetDistance( const Vector3 &p_Other ) const;
		RAS_FLOAT32 GetDistanceSquare( const Vector3 &p_Other ) const;

		void Zero( );
		void Clean( );

		void Normalise( );

		RAS_FLOAT32 Dot( const Vector3 &p_Other ) const;

		Vector3 Cross( const Vector3 &p_Other ) const;

		Vector3 operator+( const Vector3 &p_Other ) const;
		Vector3 operator-( const Vector3 &p_Other ) const;
		Vector3 operator*( const Vector3 &p_Other ) const;
		Vector3 operator*( const RAS_FLOAT32 p_Scalar ) const;
		Vector3 operator/( const Vector3 &p_Other ) const;
		Vector3 operator/( const RAS_FLOAT32 p_Scalar ) const;

		Vector3 &operator+=( const Vector3 &p_Other );
		Vector3 &operator-=( const Vector3 &p_Other );
		Vector3 &operator*=( const Vector3 &p_Other );
		Vector3 &operator*=( const RAS_FLOAT32 p_Scalar );
		Vector3 &operator/=( const Vector3 &p_Other );
		Vector3 &operator/=( const RAS_FLOAT32 p_Scalar );

	private:
		RAS_FLOAT32 m_X;
		RAS_FLOAT32 m_Y;
		RAS_FLOAT32 m_Z;
	};
}

#endif // __RASTER_VECTOR3_HPP__

