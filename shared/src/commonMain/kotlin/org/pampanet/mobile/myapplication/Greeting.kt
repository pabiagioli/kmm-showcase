package org.pampanet.mobile.myapplication

class Greeting {
    fun greeting(): String {
        return "Hello, ${Platform().platform}!"
    }
}