#pragma once

namespace isim
{
struct Plane
{
	Vector A, B, C;

	Plane()
	{
	}

	Plane(const Vector& P1, const Vector& P2, const Vector& P3) : A(P1),
			B(P2),
			C(P3)
	{
	}
};
};
