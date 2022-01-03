import org.pampanet.mobile.core.CommonTools
import org.pampanet.mobile.core.FloatUtils
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.time.ExperimentalTime

class FloatUtilsTest {

    @ExperimentalTime
    @Test
    fun testFloatUtils() {
        val mock = 36.4f
        val encoded = FloatUtils.fromSFloat(mock)
        val decoded = FloatUtils.toSFloat(CommonTools.numberToByteArray(encoded),0)
        assertEquals(decoded, mock)
    }
}