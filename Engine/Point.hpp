#ifndef POINT_HPP
#define POINT_HPP

namespace Engine {
	/// Can be used as 2D coordinate point or 2D vector.
	struct Point {
		// The coordinates of the point.
		float x, y;
		/// Construct a Point with coordinate (0, 0).
		explicit Point();
		/// Construct a Point with coordinate (x, y).
		explicit Point(float x, float y);
		/// Compare between Points.
		/// return: Determines whether the two Points have the same coordinate.
		bool operator==(const Point& rhs) const;
		bool operator!=(const Point& rhs) const;
		Point operator+(const Point& rhs) const;
		Point operator-(const Point& rhs) const;
		Point operator*(const float& rhs) const;
		Point operator/(const float& rhs) const;
		/// Make point act like vector and get the normalized vector.
		/// return: The normalized vector.
		Point Normalize() const;
		/// Make point act like vector and get the inner product.
		/// rhs: The second vector.
		/// return: The inner product.
		float Dot(const Point& rhs) const;
		/// Make point act like vector and get the squared magnitude.
		/// return: Squared magnitude of vector.
		float MagnitudeSquared() const;
		/// Make point act like vector and get the magnitude.
		/// return: Magnitude of vector.
		float Magnitude() const;
	};
	Point operator*(const float& lhs, const Point& rhs);
}
#endif // POINT_HPP
