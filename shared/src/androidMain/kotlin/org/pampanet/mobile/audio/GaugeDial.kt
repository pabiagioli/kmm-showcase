package org.pampanet.mobile.audio

import android.content.Context
import android.graphics.*
import android.os.Build
import android.util.AttributeSet

import android.view.View
import kotlin.math.cos
import kotlin.math.sin


class GaugeDial : View {
    private var gaugeDial: Path? = null
    private var mPaint: Paint? = null
    var angleDegrees = 0f
        get() = field - 180
        set(angleDegrees) {
            field = angleDegrees
            invalidate()
        }
    private val angleOffset = 180f

    constructor(context: Context?) : super(context) {
        initDial()
    }

    constructor(context: Context?, attrs: AttributeSet?) : super(context, attrs) {
        initDial()
    }

    constructor(context: Context?, attrs: AttributeSet?, defStyleAttr: Int) : super(
        context,
        attrs,
        defStyleAttr
    ) {
        initDial()
    }

    private fun initDial() {
        this.setWillNotDraw(false)
        gaugeDial = Path()
        mPaint = Paint(Paint.ANTI_ALIAS_FLAG)
        mPaint!!.style = Paint.Style.FILL_AND_STROKE
        mPaint!!.strokeWidth = 14F
        mPaint!!.color = Color.RED
        angleDegrees = 0f
    }


    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        gaugeDial?.rewind()
        val dpi: Float = resources.displayMetrics.density
        val radius: Float = this.measuredWidth / 2 - 38 * dpi
        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.SRC_ATOP)
        canvas.translate(this.measuredWidth / 2f, this.measuredWidth / 2f - 10 * dpi)
        gaugeDial?.moveTo(0f, -20 * dpi)
        gaugeDial?.addCircle(0f, -20 * dpi, 4 * dpi, Path.Direction.CW)
        gaugeDial?.moveTo(0f, -20 * dpi)
        gaugeDial?.lineTo(
            (radius * cos(Math.toRadians(angleDegrees.toDouble()))).toFloat(),
            (radius * sin(
                Math.toRadians(
                    angleDegrees.toDouble()
                )
            )).toFloat()
        )
        canvas.drawPath(gaugeDial!!, mPaint!!)
        //if (Build.VERSION.SDK_INT != Build.VERSION_CODES.M) canvas.restore()
    }
}