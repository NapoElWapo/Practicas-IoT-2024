package com.example.testubi2

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.cardview.widget.CardView
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.firebase.auth.FirebaseAuth
import java.util.ArrayList

class DevicesActivity : AppCompatActivity() {
    lateinit var deviceAdapter: DeviceAdapter
    lateinit var rvDevice: RecyclerView
    lateinit var deviceManager: RecyclerView.LayoutManager
    lateinit var logout_btn : Button
    lateinit var deviceCard : CardView

    override fun onCreate(savedInstanceState: Bundle?) {

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_devices)

        val devices = ArrayList<DeviceClass>()

        devices.add(DeviceClass("Sala de TV", "https://i1.sndcdn.com/artworks-EC5k5lHzgHPLsyzW-Uxz2Qg-t500x500.jpg"))
        devices.add(DeviceClass("Cocina", "https://i1.sndcdn.com/artworks-oRPCezBS9whT1qXQ-FHsbCg-t500x500.jpg"))

        rvDevice = findViewById(R.id.rv_device)
        deviceAdapter = DeviceAdapter(devices)
        deviceManager = GridLayoutManager(this,2)
        rvDevice.adapter = deviceAdapter
        rvDevice.layoutManager = deviceManager

        logout_btn = findViewById(R.id.logout_btn)

        logout_btn.setOnClickListener{
            val intent = Intent(this, LoginActivity::class.java)
            startActivity(intent)
            finish()
        }

    }
}