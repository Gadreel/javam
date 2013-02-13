//============================================================================
// Name        : gtmci.c
// Author      : lj
// Version     :
//============================================================================

#include <string.h>
#include "gtmxc_types.h"
#include "com_divconq_gtm_JavaM.h"

gtm_status_t checkerr(JNIEnv *env, gtm_status_t status);
gtm_status_t isGlnValid(JNIEnv *env, jstring);
gtm_status_t callgtm();
int transaction=0;

#define BUF_LEN 1024
#define KEYLEN 512
#define VARLEN 32767


#ifdef __cplusplus
extern "C" {
#endif

	JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)	{
		gtm_status_t status = checkerr(0, gtm_init());
		if (status == 0)
			return JNI_VERSION_1_2;
		else
			return JNI_ERR;
	}

	JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *jvm, void *reserved) {
		JNIEnv *env;
		if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_2)) {
			;
		} else {
			checkerr(0, gtm_exit());
		}
	}


JNIEXPORT void JNICALL Java_com_divconq_gtm_JavaM_GTMSET___3Ljava_lang_String_2_3Ljava_lang_String_2 (JNIEnv *env, jobject obj, jobjectArray globalNames, jobjectArray globalValues)
{
	jsize namesLen = (*env)->GetArrayLength(env, globalNames);
	jsize valuesLen = (*env)->GetArrayLength(env, globalValues);
	if (namesLen != valuesLen) {
		jclass exc = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
		(*env)->ThrowNew(env, exc, "Array length for GlobalNames and values must be equal");
		return;
	}

	int i=0;
	for (i=0; i<namesLen; i++) {
		jstring globalName = (*env)->GetObjectArrayElement(env, globalNames, i);
		jstring globalValue = (*env)->GetObjectArrayElement(env, globalValues, i);

		Java_com_divconq_gtm_JavaM_GTMSET__Ljava_lang_String_2Ljava_lang_String_2 (env, obj, globalName, globalValue);

		/* explicitly releasing to assist garbage collection, though not required */
		(*env)->DeleteLocalRef(env, globalName);
		(*env)->DeleteLocalRef(env, globalValue);
	}
}


JNIEXPORT void JNICALL Java_com_divconq_gtm_JavaM_GTMSET__Ljava_lang_String_2Ljava_lang_String_2 (JNIEnv *env, jobject obj, jstring globalName, jstring globalValue)
{
	isGlnValid(env, globalName);
	isGlnValid(env, globalValue);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);
	const char *strVal = (*env)->GetStringUTFChars(env, globalValue, 0);

	checkerr(env, gtm_ci("set", gln, strVal));

	(*env)->ReleaseStringUTFChars(env, globalName, strVal);
	(*env)->ReleaseStringUTFChars(env, globalValue, gln);
}


JNIEXPORT jstring JNICALL Java_com_divconq_gtm_JavaM_GTMGET (JNIEnv *env, jobject obj, jstring globalName)
{
	gtm_char_t varcontent[VARLEN];

	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("get", varcontent, gln));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(varcontent) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, varcontent);
}


JNIEXPORT void JNICALL Java_com_divconq_gtm_JavaM_GTMKILL (JNIEnv *env, jobject obj, jstring globalName)
{
	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);
	checkerr(env, gtm_ci("kill", gln));
	(*env)->ReleaseStringUTFChars(env, globalName, gln);
}


/*
 * Class:     com_divconq_gtm_JavaM
 * Method:    GTMINCREMENT
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_divconq_gtm_JavaM_GTMINCREMENT(JNIEnv *env, jobject obj, jstring globalName, jint expr)
{
	gtm_char_t value[32];

	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);
	checkerr(env, gtm_ci("increment", value, gln, expr));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(value) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, value);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_JavaM_GTMORDER (JNIEnv *env, jobject obj, jstring globalName, jint direction)
{
	gtm_char_t varcontent[KEYLEN];

	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("order", varcontent, gln, direction));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(varcontent) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, varcontent);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_JavaM_GTMQUERY (JNIEnv *env, jobject obj, jstring globalName)
{
	isGlnValid(env, globalName);

	gtm_char_t varcontent[KEYLEN];

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("query", varcontent, gln));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(varcontent) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, varcontent);
}

JNIEXPORT void JNICALL Java_com_divconq_gtm_JavaM_GTMTSTART (JNIEnv *env, jobject obj)
{
	checkerr(env, gtm_ci("tstart", ""));
	transaction = 1;
}

/*
 * Class:     com_divconq_gtm_JavaM
 * Method:    TCOMMIT
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_divconq_gtm_JavaM_GTMTCOMMIT (JNIEnv *env, jobject obj)
{
	checkerr(env, gtm_ci("tcommit", ""));
	transaction = 0;
}


#ifdef __cplusplus
}
#endif


gtm_status_t checkerr(JNIEnv *env, gtm_status_t status)
{
	if (status != 0) {
		gtm_char_t msgbuf[BUF_LEN];
		gtm_zstatus(msgbuf, BUF_LEN);

		if (env == 0) {
			printf("GT.M ERROR: %i - %s\n", status, msgbuf);
			return status;
		} else {
			jclass exc = (*env)->FindClass(env, "java/lang/Exception");
			if (exc != NULL) {
				(*env)->ThrowNew(env, exc, msgbuf);
			}
		}
	}
	return status;
}


gtm_status_t isGlnValid(JNIEnv *env, jstring gln)
{
	if (gln == NULL) {
		jclass exc = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
		(*env)->ThrowNew(env, exc, "Global name/value must not be null");
		return 0;
	} else {
		return 1;
	}
}
