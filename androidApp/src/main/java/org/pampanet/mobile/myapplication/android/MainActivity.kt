package org.pampanet.mobile.myapplication.android

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import org.pampanet.mobile.myapplication.Greeting
import android.widget.TextView
import org.pampanet.mobile.myapplication.CommonTools
import org.pampanet.mobile.myapplication.FloatUtils

fun greet(): String {
    return Greeting().greeting()
}

fun makeFloatUtilTest(): Float {
    val mock = 36.4f
    val utils = FloatUtils()
    val encoded = utils.fromSFloat(mock)
    val decoded = utils.toSFloat(CommonTools.numberToByteArray(encoded),0)
    return decoded
}

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val tv: TextView = findViewById(R.id.text_view)
        tv.text = "${greet()} ${makeFloatUtilTest()}"
    }
}
