class Ball
{
public:
  double x, y, z, radius;
  Ball(double, double, double, double);
  ~Ball();
};

Ball::Ball(double X, double Y, double Z, double R)
{
  x = X;
  y = Y;
  z = Z;
  radius = R;
}

Ball::~Ball()
{
}
