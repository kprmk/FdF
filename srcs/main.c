#include "fdf.h"

int main(void)
{
  void *mlx;
  void *window;
  
  mlx = mlx_init();
  window = mlx_new_window(mlx, 1000, 1000, "Title");
  ft_printf("start\n");

  if (window) {}
  
  mlx_loop(mlx);
  return (0);
}