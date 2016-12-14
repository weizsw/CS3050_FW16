package Dstar;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;

class MyCanvas extends Canvas
{
  private static final long serialVersionUID = 1L;
  private Graphics2D bg2;
  private BufferedImage buffer;


  public MyCanvas(Dimension paramDimension)
  {
    Initialize(paramDimension);
    setSize(paramDimension);
  }

  private void Initialize(Dimension paramDimension)
  {
    this.buffer = new BufferedImage(paramDimension.width, paramDimension.height, 1);
    this.bg2 = ((Graphics2D)this.buffer.getGraphics());
    this.bg2.setFont(new Font("Times New Roman", 1, 11));
    this.bg2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
  }

  public void Draw(Image paramImage, int paramInt1, int paramInt2)
  {
    this.bg2.drawImage(paramImage, paramInt1, paramInt2, this);
  }

  public void paint(Graphics paramGraphics)
  {
    Graphics2D localGraphics2D = (Graphics2D)paramGraphics;
    localGraphics2D.drawImage(this.buffer, 0, 0, null);
  }

  public void update(Graphics paramGraphics)
  {
    paint(paramGraphics);
  }

  public Graphics2D getGraphics2D()
  {
    return this.bg2;
  }
}