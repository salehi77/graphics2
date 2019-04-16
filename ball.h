class Ball
{
public:
  double x, y, z, radius, dx, dy, dz;
  Ball(double, double, double, double, double, double, double);
  ~Ball();
};

Ball::Ball(double X, double Y, double Z, double DX, double DY, double DZ, double R)
{
  x = X;
  y = Y;
  z = Z;
  dx = DX;
  dy = DY;
  dz = DZ;
  radius = R;
}

Ball::~Ball()
{
}
