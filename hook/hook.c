#include "../headers/cub3d.h"

int	ft_close(int keycode, t_rc *rc)
{
	exit(0);
	return (1);
}

static void	hook_WS(int keycode, t_rc *rc)
{
	if (keycode == KEY_W)
	{
		if (rc->pars->map[(int)(rc->posX + rc->dirX * SPEEDMOOVE)]
			[(int)rc->posY] != '1')
			rc->posX += rc->dirX * SPEEDMOOVE;
		if (rc->pars->map[(int)rc->posX]
			[(int)(rc->posY + rc->dirY * SPEEDMOOVE)] != '1')
			rc->posY += rc->dirY * SPEEDMOOVE;
		ft_Raycaster(rc);
	}
	if (keycode == KEY_S)
	{
		if (rc->pars->map[(int)(rc->posX - rc->dirX * SPEEDMOOVE)]
			[(int)rc->posY] != '1')
			rc->posX -= rc->dirX * SPEEDMOOVE;
		if (rc->pars->map[(int)rc->posX]
			[(int)(rc->posY - rc->dirY * SPEEDMOOVE)] != '1')
			rc->posY -= rc->dirY * SPEEDMOOVE;
		ft_Raycaster(rc);
	}
}

void	hook_LR(int keycode, t_rc *rc)
{
	double	oldDirX;
	double	oldPlaneX;

	if (keycode == KEY_RIGHT)
	{
		oldDirX = rc->dirX;
		rc->dirX = rc->dirX * cos(-SPEEDROT) - rc->dirY * sin(-SPEEDROT);
		rc->dirY = oldDirX * sin(-SPEEDROT) + rc->dirY * cos(-SPEEDROT);
		oldPlaneX = rc->planeX;
		rc->planeX = rc->planeX * cos(-SPEEDROT) - rc->planeY * sin(-SPEEDROT);
		rc->planeY = oldPlaneX * sin(-SPEEDROT) + rc->planeY * cos(-SPEEDROT);
		ft_Raycaster(rc);
		return ;
	}
	oldDirX = rc->dirX;
	rc->dirX = rc->dirX * cos(SPEEDROT) - rc->dirY * sin(SPEEDROT);
	rc->dirY = oldDirX * sin(SPEEDROT) + rc->dirY * cos(SPEEDROT);
	oldPlaneX = rc->planeX;
	rc->planeX = rc->planeX * cos(SPEEDROT) - rc->planeY * sin(SPEEDROT);
	rc->planeY = oldPlaneX * sin(SPEEDROT) + rc->planeY * cos(SPEEDROT);
	ft_Raycaster(rc);
}

void	hook_AD(int keycode, t_rc *rc)
{
	if (keycode == KEY_D)
	{
		rc->planeX -= 0.5;
		rc->planeY -= 0.5;
		ft_Raycaster(rc);
	}
	return ;
}

int	key_hook(int keycode, t_rc *rc)
{
	if (keycode == KEY_ESC)
	{
		wrdestroy();
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_S)
	{
		hook_WS(keycode, rc);
	}
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
	{
		hook_LR(keycode, rc);
	}
	if (keycode == KEY_A || keycode == KEY_D)
	{
		hook_AD(keycode, rc);
	}
	if (keycode > 0)
		printf("keycode : %f %f\n", rc->planeX, rc->planeY);
	return (0);
}
