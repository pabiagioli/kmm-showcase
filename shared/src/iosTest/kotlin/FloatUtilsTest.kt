import org.pampanet.mobile.core.CommonTools.numberToByteArray
import org.pampanet.mobile.core.FloatUtils
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
            //val utils = FloatUtils()
            val encoded = FloatUtils.fromSFloat(mock)
            val decoded = FloatUtils.toSFloat(numberToByteArray(encoded),0)
            assertEquals(decoded, mock)
        }
        println("total elapsed time : ${elapsed.toDouble(DurationUnit.MILLISECONDS)}")
    }
}