package com.example.seeaw4.seeaw4.iot;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private int r, g, b;
    private long lastTrigger;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SeekBar sb1 = findViewById(R.id.sb1);
        SeekBar sb2 = findViewById(R.id.sb2);
        SeekBar sb3 = findViewById(R.id.sb3);
        sb1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                r = progress;
                setColor();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        sb2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                g = progress;
                setColor();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        sb3.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                b = progress;
                setColor();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        Button randomBtn = findViewById(R.id.randomBtn);
        randomBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Random random = new Random();
                r = random.nextInt(256);
                g = random.nextInt(256);
                b = random.nextInt(256);
                sb1.setProgress(r);
                sb2.setProgress(g);
                sb3.setProgress(b);
                setColor();
            }
        });
        findViewById(R.id.resetBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                r = 0;
                g = 0;
                b = 0;
                sb1.setProgress(r);
                sb2.setProgress(g);
                sb3.setProgress(b);
                setColor();
            }
        });
    }


    private void setColor() {
        Log.d("progress", r + "," + g + "," + b);
        if (System.currentTimeMillis() - lastTrigger < 1000) {
            return;
        }
        lastTrigger = System.currentTimeMillis();
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Socket socket = new Socket("192.168.1.103", 1999);
                    PrintStream pw = new PrintStream(socket.getOutputStream());
                    String rStr = "";
                    String gStr = "";
                    String bStr = "";
                    if (r < 100) {
                        rStr += "0";
                        if (r < 10) {
                            rStr += "0";
                        }
                    }
                    rStr += r;

                    if (g < 100) {
                        gStr += "0";
                        if (g < 10) {
                            gStr += "0";
                        }
                    }
                    gStr += g;

                    if (b < 100) {
                        bStr += "0";
                        if (b < 10) {
                            bStr += "0";
                        }
                    }
                    bStr += b;
                    pw.println(rStr + "," + gStr + "," + bStr + "F");
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        }).start();
    }

}
