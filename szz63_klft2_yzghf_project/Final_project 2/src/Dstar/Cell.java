package Dstar;

class Cell
{
  public int g;
  public int rhs;
  public int h;
  public Cell parent;
  public int x;
  public int y;
  public byte real_type;
  public byte type_robot_vision;
  public int iteration;
  public boolean used;
  public static final byte FREE = 0;
  public static final byte WALL = 1;
  public static final byte PATH = 2;


  public Cell(int paramInt1, int paramInt2)
  {
    this.parent = null;
    this.x = paramInt1;
    this.y = paramInt2;
    this.h = 0;
    this.used = false;
    this.type_robot_vision = (this.real_type = 0);
    this.g = (this.rhs = 2147483647);
    this.iteration = 0;
  }

  public String toString()
  {
    return new String(Integer.toString(this.x + 1) + Character.toString((char)(this.y + 65)));
  }
}