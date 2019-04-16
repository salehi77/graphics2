class Page
{
private:
public:
  int width, height;
  Page(int, int);
  ~Page();
};

Page::Page(int W, int H)
{
  height = H;
  width = W;
}

Page::~Page()
{
}
