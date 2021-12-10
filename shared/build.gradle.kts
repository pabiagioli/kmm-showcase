import org.jetbrains.kotlin.gradle.plugin.mpp.DefaultCInteropSettings
import org.jetbrains.kotlin.gradle.plugin.mpp.KotlinNativeTarget
import org.jetbrains.kotlin.gradle.plugin.mpp.NativeBuildType

plugins {
    kotlin("multiplatform")
    kotlin("native.cocoapods")
    id("com.android.library")
}

version = "1.0"

val libsDir = projectDir.resolve("src/coreNative")

val androidPresets = mapOf(
    "androidNativeArm32" to "$libsDir/armeabi-v7a",
    "androidNativeArm64" to "$libsDir/arm64-v8a",
    "androidNativeX86" to "$libsDir/x86",
    "androidNativeX64" to "$libsDir/x86_64"
)

kotlin {
    android(){
        publishLibraryVariants("release")
    }
    androidNativeX86() {
        binaries { sharedLib() }//"corenative", listOf(RELEASE)) }
        configureCInterops(this)
        renameLib(this)
    }
    iosX64() {
        configureCInterops(this)
        compilations["main"].enableEndorsedLibs = true
    }
    iosArm64() {
        configureCInterops(this)
        compilations["main"].enableEndorsedLibs = true
    }
    //iosSimulatorArm64() sure all ios dependencies support this target

    cocoapods {
        summary = "Some description for the Shared Module"
        homepage = "Link to the Shared Module homepage"
        ios.deploymentTarget = "14.1"
        podfile = project.file("../iosApp/Podfile")
        framework {
            baseName = "shared"
        }
    }
    
    sourceSets {
        val commonMain by getting
        val commonTest by getting {
            dependencies {
                implementation(kotlin("test-common"))
                implementation(kotlin("test-annotations-common"))
            }
        }
        val androidMain by getting {
            dependencies {
                implementation(kotlin("stdlib-jdk8"))
            }
        }
        val androidTest by getting {
            dependencies {
                implementation(kotlin("test-junit"))
                implementation("junit:junit:4.13.2")
            }
        }
        val androidNativeX86Main by getting
        //val androidNativeX64Main by getting
        //val androidNativeArm32Main by getting
        //val androidNativeArm64Main by getting
        val androidNativeMain by creating {
            dependsOn(commonMain)
            androidNativeX86Main.dependsOn(this)
            //androidNativeX64Main.dependsOn(this)
            //androidNativeArm32Main.dependsOn(this)
            //androidNativeArm64Main.dependsOn(this)
        }

        val androidNativeX86Test by getting
        //val androidNativeX64Main by getting
        //val androidNativeArm32Main by getting
        //val androidNativeArm64Main by getting
        val androidNativeTest by creating {
            dependsOn(commonTest)
            androidNativeX86Test.dependsOn(this)
            //androidNativeX64Main.dependsOn(this)
            //androidNativeArm32Main.dependsOn(this)
            //androidNativeArm64Main.dependsOn(this)
        }

        val iosX64Main by getting
        val iosArm64Main by getting
        //val iosSimulatorArm64Main by getting
        val iosMain by creating {
            dependsOn(commonMain)
            iosX64Main.dependsOn(this)
            iosArm64Main.dependsOn(this)
            //iosSimulatorArm64Main.dependsOn(this)
        }
        val iosX64Test by getting
        val iosArm64Test by getting
        //val iosSimulatorArm64Test by getting
        val iosTest by creating {
            dependsOn(commonTest)
            iosX64Test.dependsOn(this)
            iosArm64Test.dependsOn(this)
            //iosSimulatorArm64Test.dependsOn(this)
        }

        all {
            // We use unsigned types, but do not expose them.
            // https://kotlinlang.org/docs/reference/opt-in-requirements.html
            languageSettings.optIn("kotlin.time.ExperimentalTime")
            languageSettings.optIn("kotlin.RequiresOptIn")
            languageSettings.optIn("kotlin.ExperimentalUnsignedTypes")
            languageSettings.optIn("kotlin.ExperimentalMultiplatform") // optional expectation
        }
    }
}

android {
    compileSdk = 31
    sourceSets{
        this["main"].manifest.srcFile("src/androidMain/AndroidManifest.xml")
        this["main"].setRoot("src/androidMain")
        this["main"].jniLibs.srcDir(libsDir)
    }

    defaultConfig {
        minSdk = 21
        targetSdk = 31
        ndk {
            abiFilters.addAll(listOf(
                //"armeabi-v7a",
                //"arm64-v8a",
                "x86",
                //"x86_64"
            ))
        }
    }
}


fun configureCInterops(it: KotlinNativeTarget, compilationName: String  = "main"): NamedDomainObjectContainer<DefaultCInteropSettings>? {
    it.compilations[compilationName].cinterops {
        val core by creating {
            defFile("$libsDir/core.def")
            val javaHome = File(System.getenv("JAVA_HOME"))
            headers("$javaHome/include/jni.h","$libsDir/core.h", "$libsDir/core.c")
            includeDirs(
                libsDir,
                File(javaHome, "include").absolutePath,
                File(javaHome, "include/darwin").absolutePath,
                File(javaHome, "include/linux").absolutePath,
                File(javaHome, "include/win32").absolutePath
            )
            packageName("org.pampanet.native.core")
        }
    }
    return it.compilations[compilationName].cinterops
}

fun renameLib(target: KotlinNativeTarget) {
    val libDir = androidPresets[target.name]
    NativeBuildType.values().forEach {
        val executable = target.binaries.getSharedLib(it)
        val linkTask = executable.linkTask
        val binaryFile = executable.outputFile

        linkTask.doLast {
            copy {
                from(binaryFile)
                into(File(libDir))
                rename { "libcorenative.so" }
            }
        }

        tasks.preBuild {
            dependsOn(linkTask)
        }
    }
}

println("libsDir = $libsDir")
