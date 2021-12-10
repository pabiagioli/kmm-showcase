import org.pampanet.mobile.myapplication.CommonTools
import org.pampanet.mobile.myapplication.FloatUtils
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.time.ExperimentalTime

class FloatUtilsTest {

    @ExperimentalTime
    @Test
    fun testFloatUtils() {
        val mock = 36.4f
        //val utils = FloatUtils()
        val encoded = FloatUtils.fromSFloat(mock)
        val decoded = FloatUtils.toSFloat(CommonTools.numberToByteArray(encoded),0)
        assertEquals(decoded, mock)
    }
}