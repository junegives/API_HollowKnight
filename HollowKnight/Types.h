#pragma once

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

struct Vector
{
	Vector() { }
	Vector(float x, float y) : m_fX(x), m_fY(y) { }
	Vector(POINT point) : m_fX(static_cast<float>(point.x)), m_fY(static_cast<float>(point.y)) { }

	Vector operator+(const Vector& other)
	{
		Vector temp{};
		temp.m_fX = m_fX + other.m_fX;
		temp.m_fY = m_fY + other.m_fY;

		return temp;
	}

	Vector operator-(const Vector& other)
	{
		Vector temp{};
		temp.m_fX = m_fX - other.m_fX;
		temp.m_fY = m_fY - other.m_fY;

		return temp;
	}

	void operator+=(const Vector& other)
	{
		m_fX += other.m_fX;
		m_fY += other.m_fY;
	}


	void operator-=(const Vector& other)
	{
		m_fX -= other.m_fX;
		m_fY -= other.m_fY;
	}

	Vector operator+(float value)
	{
		Vector temp{};
		temp.m_fX = m_fX + value;
		temp.m_fY = m_fY + value;

		return temp;
	}

	Vector operator-(float value)
	{
		Vector temp{};
		temp.m_fX = m_fX - value;
		temp.m_fY = m_fY - value;

		return temp;
	}

	Vector operator*(float value)
	{
		Vector temp{};
		temp.m_fX = m_fX * value;
		temp.m_fY = m_fY * value;

		return temp;
	}

	void operator*=(float value)
	{
		m_fX *= value;
		m_fY *= value;
	}

	Vector operator/(float value)
	{
		Vector temp{};
		temp.m_fX = m_fX / value;
		temp.m_fY = m_fY / value;

		return temp;
	}

	void operator/=(float value)
	{
		m_fX /= value;
		m_fY /= value;
	}

	Vector operator%(float value)
	{
		Vector temp{};
		temp.m_fX = (int)m_fX % (int)value;
		temp.m_fY = (int)m_fY % (int)value;

		return temp;
	}

	bool operator<(Vector& other)
	{
		return this->LengthSquared() < other.LengthSquared();
	}

	bool operator==(const Vector& other)
	{
		return m_fX == other.m_fX && m_fY == other.m_fY;
	}

	bool operator!=(const Vector& other)
	{
		return !(*this == other);
	}

	float LengthSquared()
	{
		return m_fX * m_fX + m_fY * m_fY;
	}

	float Length()
	{
		return ::sqrtf(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();

		if (length < 0.00000000001f)
			return;

		m_fX /= length;
		m_fY /= length;
	}

	float Distance(Vector& other)
	{
		Vector temp = { other.m_fX - this->m_fX, other.m_fY - this->m_fY };
		return temp.Length();
	}

	float Dot(Vector& other)
	{
		return m_fX * other.m_fX + m_fY * other.m_fY;
	}

	float Cross(Vector& other)
	{
		return m_fX * other.m_fY - other.m_fX * m_fY;
	}

	float m_fX = 0;
	float m_fY = 0;
};

using Pos = Vector;

struct tagLine
{	
	ELineType	eLineType = ELineType::ENUM_END;
	Vector		tLPoint;
	Vector		tRPoint;
	int			iR = 0;
	int			iG = 0;
	int			iB = 0;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(Vector _tLPoint, Vector _tRPoint) : tLPoint(_tLPoint), tRPoint(_tRPoint) {}
};

typedef struct tagFrame
{
	int			iFrameStart;
	int			iFrameEnd;
	int			iMotion;
	uint64		dwSpeed;
	uint64		dwTime;

}FRAME;

typedef struct tagTile
{
	ETileType	eTileType = ETileType::ENUM_END;
	float	fLeft;
	float	fTop;
	float	fRight;
	float	fBottom;
	int		iR = 0;
	int		iG = 0;
	int		iB = 0;

	tagTile() { ZeroMemory(this, sizeof(tagTile)); }
	tagTile(float _fLeft, float _fTop, float _fRight, float _fBottom)
		: fLeft(_fLeft), fTop(_fTop), fRight(_fRight), fBottom(_fBottom) {}
}TILE;