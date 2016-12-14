package Dstar;

import javax.swing.JFrame;

public class Dstar
{
	
  public static void main(String[] paramArrayOfString)
  {
      
      
      
    D_applet localD_applet = new D_applet();
    localD_applet.init();
    localD_applet.start();
    localD_applet.setSize(2000, 600);
    JFrame localJFrame = new JFrame("Robot");
    localJFrame.add(localD_applet);
    localJFrame.setSize(2000, 2000);
    localJFrame.setVisible(true);
    localJFrame.setDefaultCloseOperation(2);
    
    

  }
}