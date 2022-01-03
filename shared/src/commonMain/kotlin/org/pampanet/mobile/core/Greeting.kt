package org.pampanet.mobile.core

class Greeting {
    fun greeting(): String {
        return "Hello, ${Platform().platform}!"
    }
}