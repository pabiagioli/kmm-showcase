package org.pampanet.mobile.core.android

import android.Manifest.permission.RECORD_AUDIO
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import org.pampanet.mobile.core.Greeting
import android.widget.TextView
import com.vmadalin.easypermissions.EasyPermissions
import com.vmadalin.easypermissions.annotations.AfterPermissionGranted
import com.vmadalin.easypermissions.models.PermissionRequest
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.InternalCoroutinesApi
import kotlinx.coroutines.flow.flowOn
import kotlinx.coroutines.launch
import org.pampanet.mobile.audio.OboeEngine
import org.pampanet.mobile.core.CommonTools
import org.pampanet.mobile.core.FloatUtils
import org.pampanet.mobile.audio.Freq2NoteUtils
import org.pampanet.mobile.audio.Freq2NoteUtils.getNote
import org.pampanet.mobile.audio.GaugeDial


fun greet(): String {
    return Greeting().greeting()
}

fun makeFloatUtilTest(): Float {
    val mock = 36.4f
    //val utils = FloatUtils()
    val encoded = FloatUtils.fromSFloat(mock)
    val decoded = FloatUtils.toSFloat(CommonTools.numberToByteArray(encoded), 0)
    return decoded
}

@InternalCoroutinesApi
class MainActivity : AppCompatActivity() {

    val oboeEngine: OboeEngine = OboeEngine()
    var currentPitch: Float = -1f

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestMic()
        //val tv: TextView = findViewById(R.id.text_view)
        //tv.text = "${greet()} ${makeFloatUtilTest()}"

    }

    override fun onResume() {
        super.onResume()
        oboeEngine.startAudioEngine()
        GlobalScope.launch(Dispatchers.Main) {
            oboeEngine.pitchTracker().flowOn(Dispatchers.IO).collect {
                if (currentPitch != it) {
                    currentPitch = it
                    val noteFromPitch = getNote(currentPitch, false)
                    Log.d("MainActivity", "pitch = $it")
                    val noteTunner : TextView = findViewById(R.id.notaAfinadorTV)
                    val freqDisplayTV: TextView = findViewById(R.id.freqAfinadorTV)
                    val gaugeDial: GaugeDial = findViewById(R.id.pampanet_gauge_dial)
                    gaugeDial.angleDegrees = (Freq2NoteUtils.getAngleFromHz(currentPitch))
                    noteTunner.text = noteFromPitch
                    freqDisplayTV.text = "$currentPitch Hz"
                }
                //tv.text = "pitch = $it"
            }
        }
    }

    override fun onPause() {
        super.onPause()
        oboeEngine.stopAudioEngine()
    }

    fun requestMic() {
        EasyPermissions.requestPermissions(
            this,
            "This app needs permission for audio recording",
            22, RECORD_AUDIO
        )
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)

        // EasyPermissions handles the request result.
        EasyPermissions.onRequestPermissionsResult(requestCode, permissions, grantResults, this)
    }
}
