#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1024
#define screenHeight 512
#define moveSpeed 1
#define rotSpeed 0.0872665

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,6,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void			ft_clear(t_rc *rc)
{
	int x = screenHeight;
	int y = screenWidth;

	while (x--)
	{
		while (y--)
			my_mlx_pixel_put(rc, y, x, 0);
		y = screenWidth;
	}
}

char	*get_pixel(t_img *data, int x, int y)
{
	char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (dst);
}

void            my_mlx_pixel_put(t_rc *data, int x, int y, int color)
{
    char    *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	//printf("here . %x\n", *(unsigned int*)dst);
	*(unsigned int*)dst = color;
}

void	ft_verLine(int x, int drawstart, int drawend, int color, t_rc *rc)
{
	int imgx;
	int imgy;
	int len = drawend - drawstart;
	int wle = 0;
	// printf("camera : %f\n", rc->planeX);
	imgx = (int)(rc->txtn[rc->side]->img_width * (rc->wallX - (int)rc->wallX));
	imgy = (int)(((rc->txtn[rc->side]->img_height - 1) / (double)len) * wle);
	while (wle < len)
	{
		imgy = (int)(((rc->txtn[rc->side]->img_height - 1) / (double)len) * wle);
		// printf("rc->wallX : %f\n", rc->wallX);
		my_mlx_pixel_put(rc, x, drawstart, *(unsigned int*)get_pixel(rc->txtn[rc->sd], imgx, imgy));
		wle++;
		drawstart++;
	}
}

void	ft_spriteLine(int x, int drawstart, int drawend, int color, t_rc *rc)
{
	int imgx;
	int imgy;
	int len = drawend - drawstart;
	int wle = 0;

	imgx = (int)(rc->txtn[4]->img_width * (rc->wallX - (int)rc->wallX));
	imgy = (int)(((rc->txtn[4]->img_height - 1) / (double)len) * wle);
	while (wle < len)
	{
		imgy = (int)(((rc->txtn[4]->img_height - 1) / (double)len) * wle);
		// printf("rc->wallX : %f\n", rc->wallX);
		my_mlx_pixel_put(rc, x, drawstart, *(unsigned int*)get_pixel(rc->txtn[4], imgx, imgy));
		wle++;
		drawstart++;
	}
}

int             key_hook(int keycode, t_rc *rc)
{
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	if (keycode == KEY_W)
    {
      if(worldMap[(int)(rc->posX + rc->dirX * moveSpeed)][(int)(rc->posY)] == 0) rc->posX += rc->dirX * moveSpeed;
      if(worldMap[(int)(rc->posX)][(int)(rc->posY + rc->dirY * moveSpeed)] == 0) rc->posY += rc->dirY * moveSpeed;
	  ft_clear(rc);
	  ft_Raycaster(rc);
    }
    //move backwards if no wall behind you
    if (keycode == KEY_S)
    {
      if(worldMap[(int)(rc->posX - rc->dirX * moveSpeed)][(int)(rc->posY)] == 0) rc->posX -= rc->dirX * moveSpeed;
      if(worldMap[(int)(rc->posX)][(int)(rc->posY - rc->dirY * moveSpeed)] == 0) rc->posY -= rc->dirY * moveSpeed;
	  ft_clear(rc);
	  ft_Raycaster(rc);
    }
    //rotate to the right
    if (keycode == KEY_D)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = rc->dirX;
      rc->dirX = rc->dirX * cos(-rotSpeed) - rc->dirY * sin(-rotSpeed);
      rc->dirY = oldDirX * sin(-rotSpeed) + rc->dirY * cos(-rotSpeed);
      double oldPlaneX = rc->planeX;
      rc->planeX = rc->planeX * cos(-rotSpeed) - rc->planeY * sin(-rotSpeed);
      rc->planeY = oldPlaneX * sin(-rotSpeed) + rc->planeY * cos(-rotSpeed);
	  ft_clear(rc);
	  ft_Raycaster(rc);
    }
    //rotate to the left
    if (keycode == KEY_A)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = rc->dirX;
      rc->dirX = rc->dirX * cos(rotSpeed) - rc->dirY * sin(rotSpeed);
      rc->dirY = oldDirX * sin(rotSpeed) + rc->dirY * cos(rotSpeed);
      double oldPlaneX = rc->planeX;
      rc->planeX = rc->planeX * cos(rotSpeed) - rc->planeY * sin(rotSpeed);
      rc->planeY = oldPlaneX * sin(rotSpeed) + rc->planeY * cos(rotSpeed);
	  ft_clear(rc);
	  ft_Raycaster(rc);
    }
	return (0);
}

void	ft_Raycaster(t_rc *rc)
{
	int x = 0;

	
	for(int x = 0; x < screenWidth; x++)
    {
		//calculate ray position and direction
		rc->cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space
		rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
		rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
		//which box of the map we're in
		int mapX = (int)(rc->posX);
		int mapY = (int)(rc->posY);
		int sprite = 0;

		//length of ray from current position to next x or y-side
		// double sideDistX;
		// double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		rc->deltaDistX = fabs(1 / rc->rayDirX);
		rc->deltaDistY = fabs(1 / rc->rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		// int side; //was a NS or a EW wall hit?

		// Alternative code for deltaDist in case division through zero is not supported
		rc->deltaDistX = (rc->rayDirY == 0) ? 0 : ((rc->rayDirX == 0) ? 1 : fabs(1 / rc->rayDirX));
		rc->deltaDistY = (rc->rayDirX == 0) ? 0 : ((rc->rayDirY == 0) ? 1 : fabs(1 / rc->rayDirY));

		//calculate step and initial sideDist
		if (rc->rayDirX < 0)
		{
			stepX = -1;
			rc->sideDistX = (rc->posX - mapX) * rc->deltaDistX;
		}
		else
		{
			stepX = 1;
			rc->sideDistX = (mapX + 1.0 - rc->posX) * rc->deltaDistX;
		}
		if (rc->rayDirY < 0)
		{
			stepY = -1;
			rc->sideDistY = (rc->posY - mapY) * rc->deltaDistY;
		}
		else
		{
			stepY = 1;
			rc->sideDistY = (mapY + 1.0 - rc->posY) * rc->deltaDistY;
		}
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (rc->sideDistX < rc->sideDistY)
			{
				rc->sideDistX += rc->deltaDistX;
				mapX += stepX;
				rc->side = 0;
				rc->sd = 0;
			}
			else
			{
			rc->sideDistY += rc->deltaDistY;
			mapY += stepY;
			rc->side = 1;
			rc->sd = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] == 6) sprite = 1;
			if (worldMap[mapX][mapY] != 0) hit = 1;
		}
		
		if (rc->side == 0)	perpWallDist = (mapX - rc->posX + (1 - stepX) / 2) / rc->rayDirX;
		else				perpWallDist = (mapY - rc->posY + (1 - stepY) / 2) / rc->rayDirY;
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;

		int color;
		// printf("worldMap[mapX][mapY] : %d\n", worldMap[mapX][mapY]);
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0xFF2D00; break; //red
			case 2:  color = 0x00911F; break; //green
			case 3:  color = 0x00B9FF; break; //blue
			case 4:  color = 0xFFFFFF; break; //white
			default: color = 0xFBFF00; break; //yellow
		}

		//give x and y sides different brightness
		if (rc->side == 1) {color = color / 2;}

		// printf("here %f %f\n", rayDirY, rayDirX);
		// printf("ici : %f %f\n", deltaDistX, deltaDistY);
		//draw the pixels of the stripe as a vertical line

		if (rc->side == 0)
		{
			rc->wallX = rc->posY + perpWallDist * rc->rayDirY;
			if (rc->rayDirX > 0)
				rc->sd = 3;
		}
		else
		{
			rc->wallX = rc->posX + perpWallDist * rc->rayDirX;
			if (rc->rayDirY > 0)
				rc->sd = 2;
		}

		ft_verLine(x, drawStart, drawEnd, color, rc);
		if (sprite == 1)
		{
			if (rc->sideDistX < rc->sideDistY)
			{
			rc->sideDistX += (rc->deltaDistX / 2);
			// mapX += (stepX / 2);
			// rc->side = 0;
			}
			else
			{
			rc->sideDistY += (rc->deltaDistY / 2);
			// mapY += (stepY / 2);
			// rc->side = 1;
			}

			if (rc->side == 0) perpWallDist = (mapX - rc->posX + (1 - stepX) / 2) / rc->rayDirX;
			else           perpWallDist = (mapY - rc->posY + (1 - stepY) / 2) / rc->rayDirY;
			lineHeight = (int)(screenHeight / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			drawStart = -lineHeight / 2 + screenHeight / 2;
			if(drawStart < 0)drawStart = 0;
			drawEnd = lineHeight / 2 + screenHeight / 2;
			if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;
			ft_spriteLine(x, drawStart, drawEnd, color, rc);
		}
		// printf("here : %f %f\n", rc->sideDistX, rc->sideDistY);
	}
	mlx_put_image_to_window(rc->mlx, rc->win, rc->img, 0, 0);
}

int		main(void)
{
	t_rc rc;
	rc.posX = 3;
	rc.posY = 3;  //x and y start position
  	rc.dirX = -1;
	rc.dirY = 0; //initial direction vector
  	rc.planeX = 0;
	rc.planeY = 0.66; //the 2d raycaster version of camera plane
	rc.txtn = wrmalloc(sizeof(t_img *) * 5);

	int i = 0;
	while (i < 5)
	{
		rc.txtn[i] = wrmalloc(sizeof(t_img));
		i++;
	}
	rc.mlx = mlx_init();
    rc.win = mlx_new_window(rc.mlx, screenWidth, screenHeight, "RayCaster");
	mlx_hook(rc.win, 2, 1L<<0, key_hook, &rc);
	mlx_loop_hook(rc.mlx, key_hook, &rc);
	rc.img = mlx_new_image(rc.mlx, screenWidth, screenHeight);
    rc.addr = mlx_get_data_addr(rc.img, &rc.bits_per_pixel, &rc.line_length, &rc.endian);
	if (!(rc.txtn[0]->img = mlx_png_file_to_image(rc.mlx, "./MUR.png", &rc.txtn[0]->img_width, &rc.txtn[0]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[0]->addr = mlx_get_data_addr(rc.txtn[0]->img, &rc.txtn[0]->bits_per_pixel, &rc.txtn[0]->line_length, &rc.txtn[0]->endian);

	if (!(rc.txtn[1]->img = mlx_png_file_to_image(rc.mlx, "./Wall.png", &rc.txtn[1]->img_width, &rc.txtn[1]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[1]->addr = mlx_get_data_addr(rc.txtn[1]->img, &rc.txtn[1]->bits_per_pixel, &rc.txtn[1]->line_length, &rc.txtn[1]->endian);

	if (!(rc.txtn[2]->img = mlx_png_file_to_image(rc.mlx, "./Wall2.png", &rc.txtn[2]->img_width, &rc.txtn[2]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[2]->addr = mlx_get_data_addr(rc.txtn[2]->img, &rc.txtn[2]->bits_per_pixel, &rc.txtn[2]->line_length, &rc.txtn[2]->endian);

	if (!(rc.txtn[3]->img = mlx_png_file_to_image(rc.mlx, "./Wall3.png", &rc.txtn[3]->img_width, &rc.txtn[3]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[3]->addr = mlx_get_data_addr(rc.txtn[3]->img, &rc.txtn[3]->bits_per_pixel, &rc.txtn[3]->line_length, &rc.txtn[3]->endian);

	if (!(rc.txtn[4]->img = mlx_png_file_to_image(rc.mlx, "./sprite.png", &rc.txtn[4]->img_width, &rc.txtn[4]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[4]->addr = mlx_get_data_addr(rc.txtn[4]->img, &rc.txtn[4]->bits_per_pixel, &rc.txtn[4]->line_length, &rc.txtn[4]->endian);
	
	ft_Raycaster(&rc);
	mlx_put_image_to_window(rc.mlx, rc.win, rc.img, 0, 0);
	mlx_loop(rc.mlx);
}