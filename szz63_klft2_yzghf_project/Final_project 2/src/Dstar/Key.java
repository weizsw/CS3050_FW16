package Dstar;

import java.util.Comparator;

class Key
{
  private int a;
  private int b;
  public Cell cell;

  public Key(Cell paramCell)
  {
    this.a = Math.min(paramCell.g, paramCell.rhs);
    this.b = this.a;
    this.a = (this.a == 2147483647 ? this.a : this.a + paramCell.h);
    this.cell = paramCell;
  }

  public String toString()
  {
    return new String("[" + this.a + "," + this.b + "] => " + this.cell);
  }

  public static class Key_comparator implements Comparator<Object>
  {
    public int compare(Key paramKey1, Key paramKey2)
    {
      if (paramKey1.a == paramKey2.a)
      {
        if (paramKey1.b == paramKey2.b)
        {
          if (paramKey1.cell.x == paramKey2.cell.x)
          {
            if (paramKey1.cell.y == paramKey2.cell.y) {
              return 0;
            }
            return paramKey1.cell.y - paramKey2.cell.y;
          }

          return paramKey1.cell.x - paramKey2.cell.x;
        }

        return paramKey1.b - paramKey2.b;
      }

      return paramKey1.a - paramKey2.a;
    }

    public boolean equals(Object paramObject)
    {
      return false;
    }

    public int compare(Object Object1, Object Object2)
    {
      return compare((Key)Object1, (Key)Object2);
    }
  }
}