//============================================================================
// Name        : gtmci.c
// Author      : lj
// Version     :
//============================================================================

#include <string.h>
#include "gtmxc_types.h"
#include "com_divconq_gtm_M.h"

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

JNIEXPORT void JNICALL Java_com_divconq_gtm_M_set(JNIEnv *env, jobject obj, jstring globalName, jstring globalValue)
{
	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);
	
	if (gln == NULL) {
		checkerr(env, gtm_ci("set", gln, NULL));
	} else {
		const char *strVal = (*env)->GetStringUTFChars(env, globalValue, 0);

		checkerr(env, gtm_ci("set", gln, strVal));

		(*env)->ReleaseStringUTFChars(env, globalValue, strVal);
	}

	(*env)->ReleaseStringUTFChars(env, globalName, gln);
}

JNIEXPORT void JNICALL Java_com_divconq_gtm_M_kill(JNIEnv *env, jobject obj, jstring globalName)
{
	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);
	checkerr(env, gtm_ci("kill", gln));
	(*env)->ReleaseStringUTFChars(env, globalName, gln);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_increment(JNIEnv *env, jobject obj, jstring globalName, jint amt)
{
	gtm_char_t value[32];

	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);
	checkerr(env, gtm_ci("increment", value, gln, amt));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(value) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, value);
}

JNIEXPORT void JNICALL Java_com_divconq_gtm_M_merge(JNIEnv *env, jobject obj, jstring dest, jstring src) 
{
	isGlnValid(env, dest);
	isGlnValid(env, src);

	const char *glndest = (*env)->GetStringUTFChars(env, dest, 0);
	const char *glnsrc = (*env)->GetStringUTFChars(env, src, 0);
	
	checkerr(env, gtm_ci("merge", glndest, glnsrc));
	
	(*env)->ReleaseStringUTFChars(env, dest, glndest);
	(*env)->ReleaseStringUTFChars(env, src, glnsrc);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_get(JNIEnv *env, jobject obj, jstring globalName)
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

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_data(JNIEnv *env, jobject obj, jstring globalName)
{
	gtm_char_t varcontent[VARLEN];

	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("data", varcontent, gln));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(varcontent) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, varcontent);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_next (JNIEnv *env, jobject obj, jstring globalName)
{
	gtm_char_t varcontent[KEYLEN];

	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("order", varcontent, gln, 1));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(varcontent) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, varcontent);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_previous (JNIEnv *env, jobject obj, jstring globalName)
{
	gtm_char_t varcontent[KEYLEN];

	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("order", varcontent, gln, -1));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);

	if (strlen(varcontent) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, varcontent);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_query(JNIEnv *env, jobject obj, jstring globalName)
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

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_lock(JNIEnv *env, jobject obj, jstring globalName)
{
	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("lock", gln));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_unlock(JNIEnv *env, jobject obj, jstring globalName)
{
	isGlnValid(env, globalName);

	const char *gln = (*env)->GetStringUTFChars(env, globalName, 0);

	checkerr(env, gtm_ci("unlock", gln));

	(*env)->ReleaseStringUTFChars(env, globalName, gln);
}
  
JNIEXPORT void JNICALL Java_com_divconq_gtm_M_tStart(JNIEnv *env, jobject obj)
{
	checkerr(env, gtm_ci("tstart", ""));
	transaction = 1;
}

JNIEXPORT void JNICALL Java_com_divconq_gtm_M_tCommit(JNIEnv *env, jobject obj)
{
	checkerr(env, gtm_ci("tcommit", ""));
	transaction = 0;
}

JNIEXPORT void JNICALL Java_com_divconq_gtm_M_tRollback(JNIEnv *env, jobject obj)
{
	checkerr(env, gtm_ci("trollback", ""));
	transaction = 0;
}

JNIEXPORT jstring JNICALL Java_com_divconq_gtm_M_func(JNIEnv *env, jobject obj, jstring name, jstring args)
{
	gtm_char_t varcontent[VARLEN];

	// TODO not really valid check
	isGlnValid(env, name);
	isGlnValid(env, args);

	const char *gname = (*env)->GetStringUTFChars(env, name, 0);
	const char *gargs = (*env)->GetStringUTFChars(env, args, 0);

	checkerr(env, gtm_ci("func", varcontent, gname, gargs));

	(*env)->ReleaseStringUTFChars(env, name, gname);
	(*env)->ReleaseStringUTFChars(env, args, gargs);

	if (strlen(varcontent) == 0)
		return NULL;
	else
		return (*env)->NewStringUTF(env, varcontent);
}

JNIEXPORT void JNICALL Java_com_divconq_gtm_M_proc(JNIEnv *env, jobject obj, jstring name, jstring args)
{
	// TODO not really valid check
	isGlnValid(env, name);
	isGlnValid(env, args);

	const char *gname = (*env)->GetStringUTFChars(env, name, 0);
	const char *gargs = (*env)->GetStringUTFChars(env, args, 0);

	checkerr(env, gtm_ci("proc", gname, gargs));

	(*env)->ReleaseStringUTFChars(env, name, gname);
	(*env)->ReleaseStringUTFChars(env, args, gargs);
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
