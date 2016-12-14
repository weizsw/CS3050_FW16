package Dstar;

import java.applet.Applet;
import java.awt.Button;
import java.awt.Checkbox;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Label;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javafx.stage.Stage;
import javafx.stage.Window;


public class D_applet extends Applet
  implements ActionListener, ItemListener, KeyListener, MouseListener
{
  Maze maze;
  MyCanvas canvas1;
  MyCanvas canvas2;
  boolean place_start;
  boolean place_goal;
  boolean single_step;
  boolean executing;
  boolean first_change;
  Button read_file;
  Button restart;
  Button move;
  Button next_step;
  Button change_start;
  Button change_goal;
  Button show_result;
  Checkbox single_step_execution;
  Checkbox diagonals;
  TextArea ta;
  
  public Stage stage;
  private static final long serialVersionUID = 1L;

  public void init()
  {
      FileInputStream fis = null;
      try {
          GridBagConstraints localGridBagConstraints = new GridBagConstraints();
          Container localContainer = new Container();
          localContainer.setLayout(new FlowLayout());
          long l = (long)(Math.random() * 9.223372036854776E+018D);
          System.out.println("Please enther the absolute filepath:");
          System.out.println("e.g: /Users/Zwei/NetBeansProjects/read_file_button/src/input_file.txt");
          Scanner in = new Scanner(System.in);
          String s = in.nextLine();
          fis = new FileInputStream(s);
          
          
          BufferedReader br = new BufferedReader(new InputStreamReader(fis));
          String line = null;
          Integer size = null;
          Integer startX = null, startY = null;
          Integer endX = null, endY = null;
          Integer startxFirstob = null, startyFirstob = null, speedFirstob = null;
          Integer startxSecondob = null, startySecondob = null, obj2speed = null;
          Integer xFirstob = null, yFirstob = null;
          Integer xSecondob = null, ySecondob = null;
          line = br.readLine();
          for (char c : line.toCharArray()) {
              if(!Character.isDigit(c)) {
                  throw new IOException();
              }
          } size = Integer.parseInt(line);
          line = br.readLine();
          String token;
          token = "\\((\\d+),(\\d+)\\)";
          Pattern r = Pattern.compile(token);
          Matcher matcher = r.matcher(line);
          if(matcher.find()) {
              startX = Integer.parseInt(matcher.group(1));
              startY = Integer.parseInt(matcher.group(2));
          } else {
              throw new IOException();
          } line = br.readLine();
          matcher = r.matcher(line);
          if(matcher.find()) {
              endX = Integer.parseInt(matcher.group(1));
              endY = Integer.parseInt(matcher.group(2));
          } else {
              throw new IOException();
          } line = br.readLine();
          matcher = r.matcher(line);
          if(matcher.find()) {
              startxFirstob = Integer.parseInt(matcher.group(1));
              startyFirstob = Integer.parseInt(matcher.group(2));
          } else {
              throw new IOException();
          } line = br.readLine();
          for (char c : line.toCharArray()) {
              if(!Character.isDigit(c)) {
                  throw new IOException();
              }
          } speedFirstob = Integer.parseInt(line);
          line = br.readLine();
          String token2;
          token2 = "\\((\\+?)(-?)(\\d),(\\+?)(-?)(\\d)\\)";
          Pattern q = Pattern.compile(token2);
          matcher = q.matcher(line);
          if(matcher.find()) {
              
              if(matcher.group(3).equals("0")) {
                  if(!matcher.group(1).isEmpty() && !matcher.group(2).isEmpty()) {
                      throw new IOException();
                  }
                  xFirstob = Integer.parseInt(matcher.group(3));
                  System.out.println("Worked");
              }
              if(matcher.group(1).equals("+")) {
                  if(!matcher.group(2).isEmpty() || !matcher.group(3).equals("1")) {
                      throw new IOException();
                  }
                  xFirstob = Integer.parseInt(matcher.group(3));
              }
              if(matcher.group(2).equals("-")) {
                  if(!matcher.group(1).isEmpty() || !matcher.group(3).equals("1")) {
                      throw new IOException();
                  }
                  xFirstob = -1 * Integer.parseInt(matcher.group(3));
              }
              
              if(matcher.group(6).equals("0")) {
                  if(!matcher.group(4).isEmpty() || !matcher.group(5).isEmpty()) {
                      throw new IOException();
                  }
                  yFirstob = Integer.parseInt(matcher.group(6));
                  System.out.println("Worked");
              }
              if(matcher.group(4).equals("+")) {
                  if(!matcher.group(5).isEmpty() || !matcher.group(6).equals("1")) {
                      throw new IOException();
                  }
                  yFirstob = Integer.parseInt(matcher.group(6));
              }
              if(matcher.group(5).equals("-")) {
                  if(!matcher.group(4).isEmpty() || !matcher.group(6).equals("1")) {
                      throw new IOException();
                  }
                  yFirstob = -1 * Integer.parseInt(matcher.group(6));
              }
          } else {
              throw new IOException();
          } line = br.readLine();
          matcher = r.matcher(line);
          if(matcher.find()) {
              startxSecondob = Integer.parseInt(matcher.group(1));
              startySecondob = Integer.parseInt(matcher.group(2));
          } else {
              throw new IOException();
          } line = br.readLine();
          for (char c : line.toCharArray()) {
              if(!Character.isDigit(c)) {
                  throw new IOException();
              }
          } obj2speed = Integer.parseInt(line);
          line = br.readLine();
          matcher = q.matcher(line);
          if(matcher.find()) {
              
              if(matcher.group(3).equals("0")) {
                  if(!matcher.group(1).isEmpty() && !matcher.group(2).isEmpty()) {
                      throw new IOException();
                  }
                  xSecondob = Integer.parseInt(matcher.group(3));
              }
              if(matcher.group(1).equals("+")) {
                  if(!matcher.group(2).isEmpty() || !matcher.group(3).equals("1")) {
                      throw new IOException();
                  }
                  xSecondob = Integer.parseInt(matcher.group(3));
              }
              if(matcher.group(2).equals("-")) {
                  if(!matcher.group(1).isEmpty() || !matcher.group(3).equals("1")) {
                      throw new IOException();
                  }
                  xSecondob = -1 * Integer.parseInt(matcher.group(3));
              }
              
              if(matcher.group(6).equals("0")) {
                  if(!matcher.group(4).isEmpty() || !matcher.group(5).isEmpty()) {
                      throw new IOException();
                  }
                  ySecondob = Integer.parseInt(matcher.group(6));
              }
              if(matcher.group(4).equals("+")) {
                  if(!matcher.group(5).isEmpty() || !matcher.group(6).equals("1")) {
                      throw new IOException();
                  }
                  ySecondob = Integer.parseInt(matcher.group(6));
              }
              if(matcher.group(5).equals("-")) {
                  if(!matcher.group(4).isEmpty() || !matcher.group(6).equals("1")) {
                      throw new IOException();
                  }
                  ySecondob = -1 * Integer.parseInt(matcher.group(6));
              }
          } else {
              throw new IOException();
          } System.out.println("Room size: " + size);
          System.out.println("Robot start x: " + startX + " and Robot start y: " + startY);
          System.out.println("Robot exit x: " + endX + " and Robot exit y: " + endY);
          System.out.println("First obstacle start x: " + startxFirstob + " and y: " + startyFirstob);
          System.out.println("Speed of first obstacle: " + speedFirstob);
          System.out.println("Second obstacle start x: " + startxSecondob + " and y: " + startySecondob);
          System.out.println("Speed of second obstacle: " + obj2speed);
          System.out.println("First obstacle direction x: " + xFirstob + " and y: " + yFirstob);
          System.out.println("Second obstacle direction x: " + xSecondob + " and y: " + ySecondob);
          //asdfsdafadsdfasfadssdf
          
          
          this.maze = new Maze(l, size, size, startX, startY, endX, endY, startxFirstob, startyFirstob, speedFirstob, startxSecondob, startySecondob, obj2speed, xFirstob, yFirstob, xSecondob, ySecondob);//改地图大小
          this.maze.Get_data(speedFirstob, obj2speed, xFirstob, yFirstob, xSecondob, ySecondob, size, startxFirstob, startyFirstob, startxSecondob, startySecondob);
          
          this.canvas1 = new MyCanvas(this.maze.Printed_maze_size());
          this.canvas2 = new MyCanvas(this.maze.Printed_maze_size());
          setLayout(new GridBagLayout());
          localGridBagConstraints.insets = new Insets(0, 3, 0, 0);
          localGridBagConstraints.fill = 0;
          localGridBagConstraints.gridx = 0;
          localGridBagConstraints.gridy = 0;
          localGridBagConstraints.gridheight = 1;
          localGridBagConstraints.gridwidth = 1;
          Label localLabel1 = new Label("Map", 1);
          localLabel1.setFont(new Font("SansSerif", 3, 30));
          add(localLabel1, localGridBagConstraints);
          localGridBagConstraints.fill = 0;
          localGridBagConstraints.gridx = 1;
          localGridBagConstraints.gridy = 0;
          localGridBagConstraints.gridheight = 1;
          localGridBagConstraints.gridwidth = 1;
          Label localLabel2 = new Label("Show results", 1);
          localLabel2.setFont(new Font("SansSerif", 3, 30));
          add(localLabel2, localGridBagConstraints);
          localGridBagConstraints.fill = 2;
          localGridBagConstraints.gridx = 2;
          localGridBagConstraints.gridy = 0;
          localGridBagConstraints.gridheight = 1;
          localGridBagConstraints.gridwidth = 1;
          Label localLabel3 = new Label("D* Lite", 1);
          localLabel3.setFont(new Font("黑体", 2, 14));
          add(localLabel3, localGridBagConstraints);
          localGridBagConstraints.fill = 0;
          localGridBagConstraints.gridx = 0;
          localGridBagConstraints.gridy = 1;
          localGridBagConstraints.gridheight = 1;
          localGridBagConstraints.gridwidth = 1;
          add(this.canvas1, localGridBagConstraints);
          localGridBagConstraints.fill = 0;
          localGridBagConstraints.gridx = 1;
          localGridBagConstraints.gridy = 1;
          localGridBagConstraints.gridheight = 1;
          localGridBagConstraints.gridwidth = 1;
          add(this.canvas2, localGridBagConstraints);
          localGridBagConstraints.fill = 3;
          localGridBagConstraints.gridx = 2;
          localGridBagConstraints.gridy = 1;
          localGridBagConstraints.gridheight = 1;
          localGridBagConstraints.gridwidth = 1;
          this.ta = new TextArea("", 1, 12, 3);
          this.ta.setFocusable(false);
          add(this.ta, localGridBagConstraints);
          localGridBagConstraints.fill = 1;
          localGridBagConstraints.gridx = 0;
          localGridBagConstraints.gridy = 2;
          localGridBagConstraints.gridheight = 1;
          localGridBagConstraints.gridwidth = 3;
          add(localContainer, localGridBagConstraints);
          this.restart = new Button("Reset Everything");
          this.change_start = new Button("Set starting location");
          this.change_goal = new Button("Set exit location");
          this.move = new Button("Move step by step");
          this.next_step = new Button("Next step");
          this.show_result = new Button("Show result");
          this.read_file = new Button("Read file");
          this.single_step_execution = new Checkbox("Step by step");
          this.diagonals = new Checkbox("Robot can move along diagonal");
          this.move.addActionListener(this);
          localContainer.add(this.move);
          this.change_start.addActionListener(this);
          localContainer.add(this.change_start);
          this.change_goal.addActionListener(this);
          localContainer.add(this.change_goal);
          this.restart.addActionListener(this);
          localContainer.add(this.restart);
          this.show_result.addActionListener(this);
          localContainer.add(this.show_result);
          this.next_step.addActionListener(this);//////////
          localContainer.add(this.next_step);//////////////
          this.read_file.addActionListener(this);
          localContainer.add(this.read_file);
          this.next_step.setEnabled(false);/////
          this.next_step.addActionListener(this);
          this.single_step_execution.addItemListener(this);
          this.diagonals.addItemListener(this);
          localContainer.add(this.diagonals);
          this.canvas1.addMouseListener(this);
          this.canvas1.addKeyListener(this);
          this.canvas2.addMouseListener(this);
          this.canvas2.addKeyListener(this);
          this.executing = (this.single_step = this.place_start = this.place_goal = false);
          this.first_change = true;
          this.maze.Initialize();
          this.maze.Calculate_path(this.single_step);
          this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
          this.maze.Draw_maze(this.canvas2.getGraphics2D());
          this.canvas1.repaint();
          this.canvas2.repaint();
          this.ta.setText(this.maze.Get_stack());
      } catch (FileNotFoundException ex) {
          Logger.getLogger(D_applet.class.getName()).log(Level.SEVERE, null, ex);
      } catch (IOException ex) {
          Logger.getLogger(D_applet.class.getName()).log(Level.SEVERE, null, ex);
      } finally {
          try {
              fis.close();
          } catch (IOException ex) {
              Logger.getLogger(D_applet.class.getName()).log(Level.SEVERE, null, ex);
          }
      }
  }

  public void stop()
  {
  }

  public void mouseClicked(MouseEvent paramMouseEvent)
  {
  }

  public void mouseEntered(MouseEvent paramMouseEvent)
  {
  }

  public void mouseExited(MouseEvent paramMouseEvent)
  {
  }

  public void mousePressed(MouseEvent paramMouseEvent)
  {
    if (paramMouseEvent.getButton() == 3)
    {
      this.maze.Print_cell(paramMouseEvent.getX(), paramMouseEvent.getY());
      return;
    }
    if (this.place_start)
    {
      this.maze.Set_start(paramMouseEvent.getX(), paramMouseEvent.getY());
      this.place_start = false;
      Set_buttons_enabled(true);
    }
    else if (this.place_goal)
    {
      this.maze.Set_goal(paramMouseEvent.getX(), paramMouseEvent.getY());
      this.place_goal = false;
      Set_buttons_enabled(true);
    } else {
      if (this.executing)
      {
        return;
      }

      this.maze.Transform_cell(paramMouseEvent.getX(), paramMouseEvent.getY());
      this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
      //this.maze.Draw_maze(this.canvas2.getGraphics2D());//add//
      this.canvas1.repaint();
      //this.canvas2.repaint();//add

      return;
    }
    this.first_change = true;
    this.maze.Calculate_path(this.single_step);
    this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
    this.maze.Draw_maze(this.canvas2.getGraphics2D());
    if (this.single_step)
    {
      this.executing = true;
      this.next_step.setEnabled(true);
    }
    this.ta.setText(this.maze.Get_stack());
    if (this.maze.Execution_end())
    {
      this.next_step.setEnabled(false);
      this.executing = false;
    }
    this.canvas1.repaint();
    this.canvas2.repaint();
  }

  public void mouseReleased(MouseEvent paramMouseEvent)
  {
  }

  public void keyPressed(KeyEvent paramKeyEvent)
  {
  }

  public void keyReleased(KeyEvent paramKeyEvent)
  {
  }

  public void keyTyped(KeyEvent paramKeyEvent)
  {
  }
  
  /*public void Zidong(){
	  int cishu=0;
	  
	 //点击move step by step
	 //while(cishu==0)
	  {
	  this.first_change = true;
      this.maze.Move(this.single_step);
      this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
      this.maze.Draw_maze(this.canvas2.getGraphics2D());
      this.canvas1.repaint();
      this.canvas2.repaint();
      if ((!this.maze.Execution_end()) || (this.maze.Reached_goal()))
      {
        this.move.setEnabled(false);
        if (this.single_step)
        {
          this.next_step.setEnabled(true);
          this.executing = true;
        }
      }
      this.ta.setText(this.maze.Get_stack());
      //障碍移动
      
      

      this.maze.Obstacal(18,18,2,3,1,1,-1, -1);
      System.out.println(cishu);
      this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
      this.maze.Draw_maze(this.canvas2.getGraphics2D());//add//
      this.canvas1.repaint();
      this.canvas2.repaint();//add

      //点击setstarting，然后应该选位置了
      Set_buttons_enabled(false);
      this.place_start = true;
      cishu=this.maze.Set_newstart();
      this.place_start = false;
      Set_buttons_enabled(true);
	  }

  }*/
  public void Zidong(){
	  int fanhui=0;
	  //while(fanhui!=2){
	  /*模拟点击move step by step*/
	  this.first_change = true;
      this.maze.Move(this.single_step);
      this.maze.Draw_real_maze1(this.canvas1.getGraphics2D());
      this.maze.Draw_maze(this.canvas2.getGraphics2D());
      this.canvas1.repaint();
      this.canvas2.repaint();
      if ((!this.maze.Execution_end()) || (this.maze.Reached_goal()))
      {
        this.move.setEnabled(false);
        if (this.single_step)
        {
          this.next_step.setEnabled(true);
          this.executing = true;
        }
      }
      this.ta.setText(this.maze.Get_stack());
      //zhangai
      if (this.executing!=true)
      {
    	  this.maze.Obstacal();
          this.maze.Obstacal2();
          this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
          //this.maze.Draw_maze(this.canvas2.getGraphics2D());//add//
          this.canvas1.repaint();
          //this.canvas2.repaint();//add
      }

     
      
      //衔接是robot位置成为newstart
      /*Set start location*/
      /*Set_buttons_enabled(false);
      this.place_start = true;*/
      ////????????
      
      fanhui=this.maze.Set_newstart();
     // this.place_start = false;
      //Set_buttons_enabled(true);     
      this.first_change = true;
      this.maze.Calculate_path(this.single_step);
      this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
      this.maze.Draw_maze(this.canvas2.getGraphics2D());
      if (this.single_step)
      {
        this.executing = true;
        this.next_step.setEnabled(true);
      }
      this.ta.setText(this.maze.Get_stack());
      if (this.maze.Execution_end())
      {
        this.next_step.setEnabled(false);
        this.executing = false;
      }
      this.canvas1.repaint();
      this.canvas2.repaint();
      //while 结束后画出整个Draw path
      /*try{
    	  Thread.sleep(1000);
      }
      catch(InterruptedException e){
    	  return;
      }*/
      /*for(long iii=0;iii<111111111;iii++){
    	  int mmmm=1;
      }*/
	  //}
	  this.maze.Draw_real_maze1(this.canvas1.getGraphics2D());
  }

  public void actionPerformed(ActionEvent paramActionEvent)
  {
    if (paramActionEvent.getActionCommand().equals("Next step"))
    {
      this.maze.Calculate_path(this.single_step);
      this.maze.Draw_maze(this.canvas2.getGraphics2D());
     this.canvas2.repaint();
      if (this.maze.Execution_end())
      {
        this.next_step.setEnabled(false);
        this.move.setEnabled(true);
        this.executing = false;
      }
      this.ta.setText(this.maze.Get_stack());
    }
    else if (paramActionEvent.getActionCommand().equals("Show result")){
    	Zidong();
    }
    else if (paramActionEvent.getActionCommand().equals("Reset Everything"))
    {
      this.first_change = true;
      this.maze.Initialize();
      this.maze.Calculate_path(this.single_step);
      this.maze.Draw_maze(this.canvas2.getGraphics2D());
      this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
      this.canvas1.repaint();
      this.canvas2.repaint();
      this.move.setEnabled(true);
      this.next_step.setEnabled(false);
      this.executing = false;
      if (!this.maze.Execution_end())
      {
        this.next_step.setEnabled(true);
        this.move.setEnabled(false);
        this.executing = true;
      }
      this.ta.setText(this.maze.Get_stack());
    }
    else if (paramActionEvent.getActionCommand().equals("Set starting location"))
    {
      Set_buttons_enabled(false);
      this.place_start = true;
    }
    else if (paramActionEvent.getActionCommand().equals("Set exit location"))
    {
      Set_buttons_enabled(false);
      this.place_goal = true;
    }
    else if (paramActionEvent.getActionCommand().equals("Move step by step"))
    {
      this.first_change = true;
      this.maze.Move(this.single_step);
      this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
      this.maze.Draw_maze(this.canvas2.getGraphics2D());
      this.canvas1.repaint();
      this.canvas2.repaint();
      if ((!this.maze.Execution_end()) || (this.maze.Reached_goal()))
      {
        this.move.setEnabled(false);
        if (this.single_step)
        {
          this.next_step.setEnabled(true);
          this.executing = true;
        }
      }
      this.ta.setText(this.maze.Get_stack());
    }
    else if(paramActionEvent.getActionCommand().equals("Read file")) {
        

    }
  }

  public void itemStateChanged(ItemEvent paramItemEvent)
  {
    System.out.println();
    if (((String)paramItemEvent.getItem()).equals("Robot can move along diagonal"))
    {
      this.first_change = true;
      this.maze.Set_diagonal(this.diagonals.getState());
      this.maze.Initialize();
      this.maze.Calculate_path(this.single_step);
      this.maze.Draw_maze(this.canvas2.getGraphics2D());
      this.maze.Draw_real_maze(this.canvas1.getGraphics2D());
      if (this.single_step)
      {
        this.executing = true;
        this.next_step.setEnabled(true);
      }
      this.ta.setText(this.maze.Get_stack());
      if (this.maze.Execution_end())
      {
        this.next_step.setEnabled(false);
        this.executing = false;
      }
      this.canvas1.repaint();
      this.canvas2.repaint();
    }
    else {
      this.single_step = (!this.single_step);
    }
  }

  private void Set_buttons_enabled(boolean paramBoolean)
  {
    this.change_start.setEnabled(paramBoolean);
    this.change_goal.setEnabled(paramBoolean);
    this.move.setEnabled(paramBoolean);
    this.next_step.setEnabled(paramBoolean);
    this.single_step_execution.setEnabled(paramBoolean);
    this.diagonals.setEnabled(paramBoolean);
    this.restart.setEnabled(paramBoolean);
  }
  
 
}