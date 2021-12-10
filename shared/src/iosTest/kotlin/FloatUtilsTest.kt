import org.pampanet.mobile.myapplication.CommonTools.numberToByteArray
import org.pampanet.mobile.myapplication.FloatUtils
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.time.DurationUnit
import kotlin.time.ExperimentalTime
import kotlin.time.measureTime

class FloatUtilsTest {
    @Test
    @ExperimentalTime
    fun testFloatUtils() {
        val elapsed = measureTime {
            val mock = 36.4f
            val utils = FloatUtils()
            val encoded = utils.fromSFloat(mock)
            val decoded = utils.toSFloat(numberToByteArray(encoded),0)
            assertEquals(decoded, mock)
        }
        println("total elapsed time : ${elapsed.toDouble(DurationUnit.MILLISECONDS)}")
    }
}