package org.pampanet.mobile.audio

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.Path
import android.util.AttributeSet
import android.view.Gravity
import android.view.View
import android.widget.FrameLayout


class PampaNetGauge : View {
    private var gaugeArc: Path? = null
    private var mPaint: Paint? = null
    private var dialFrame: FrameLayout? = null
    private var angleInDegrees = 0f

    constructor(context: Context?) : super(context) {
        initGauge()
    }

    constructor(context: Context?, attrs: AttributeSet?) : super(context, attrs) {
        initGauge()
    }

    constructor(context: Context?, attrs: AttributeSet?, defStyleAttr: Int) : super(
        context,
        attrs,
        defStyleAttr
    ) {
        initGauge()
    }

    private fun initGauge() {
        this.setWillNotDraw(false)
        gaugeArc = Path()
        mPaint = Paint(Paint.ANTI_ALIAS_FLAG)
        val frameParams: FrameLayout.LayoutParams =
            FrameLayout.LayoutParams(this.measuredWidth, this.measuredHeight)
        dialFrame = FrameLayout(this.context)
        dialFrame!!.layoutParams = frameParams
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        val dpi: Float = resources.displayMetrics.density
        val radius: Float = this.measuredWidth / 2 - 20 * dpi
        mPaint!!.color = Color.rgb(0xbd, 0xbd, 0xbd)
        mPaint!!.style = Paint.Style.STROKE
        mPaint!!.strokeWidth = 2 * dpi
        //canvas.translate(0, 0);
        //gaugeArc.addArc(new RectF(0, 0, this.getMeasuredWidth(), this.getMeasuredHeight() * 2 ), 0, -180);
        gaugeArc!!.addCircle(
            measuredWidth / 2f,
            measuredWidth / 2 - 10 * dpi,
            radius,
            Path.Direction.CW
        )
        canvas.drawPath(gaugeArc!!, mPaint!!)
        canvas.save()
        canvas.translate(this.measuredWidth / 2f, this.measuredWidth / 2 - 10 * dpi)
        drawTenthsLines(canvas)
        canvas.restore()
        //drawDial(canvas);
    }

    private fun drawTenthsLines(canvas: Canvas) {
        val dpi: Float = resources.displayMetrics.density
        //mPaint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC));
        val radius: Float = this.measuredWidth / 2 - 20 * dpi
        mPaint!!.style = Paint.Style.STROKE
        var i = 180
        while (i <= 360) {
            val line = Path()
            if (i % 90 == 0) mPaint!!.color = Color.RED else mPaint!!.color = Color.BLACK
            line.moveTo(
                ((radius - 14 * dpi) * Math.cos(Math.toRadians(i.toDouble()))).toFloat(),
                ((radius - 14 * dpi) * Math.sin(Math.toRadians(i.toDouble()))).toFloat()
            )
            line.lineTo(
                ((radius - 6 * dpi) * Math.cos(Math.toRadians(i.toDouble()))).toFloat(),
                ((radius - 6 * dpi) * Math.sin(Math.toRadians(i.toDouble()))).toFloat()
            )
            canvas.drawPath(line, mPaint!!)
            i += 5
        }
    }

    fun setAngleInDegrees(degrees: Float) {
        angleInDegrees = degrees
        invalidate()
    }

    private fun drawDial(canvas: Canvas) {
        val dial: View = GaugeDial(this.context)
        dialFrame!!.addView(dial)
        val dpi: Float = resources.displayMetrics.density
        val dialParams = FrameLayout.LayoutParams(
            (22 * dpi).toInt(),
            (150 * dpi).toInt()
        )
        dialParams.topMargin = (20 * dpi).toInt()
        dialParams.gravity = Gravity.CENTER
        dial.layoutParams = dialParams
        dialFrame!!.measure(measuredWidth, measuredHeight)
        dialFrame!!.layout(0, 0, measuredWidth, measuredHeight)
        dialFrame!!.draw(canvas)
        dial.pivotX = dial.measuredWidth / 2f
        dial.pivotY = dial.measuredHeight - 20 * dpi
        dial.rotation = angleInDegrees
    }
}