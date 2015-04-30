/*******************************************************************************
 * This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *     Ilya Mizus
 *******************************************************************************/

#include "swt.h"
#include "os_structs.h"
#include "os_stats.h"

JNIEXPORT void JNICALL Java_org_eclipse_swt_graphics_GC_applyAlpha
	(JNIEnv *env, jclass that, jbyteArray jSrcData, jbyteArray jAlphaData, jint srcWidth, jint srcHeight, jint imgWidth, jint imgHeight, jint srcX, jint srcY)
{
	char *srcData, *alphaData;
#ifdef JNI_VERSION_1_2
	if (IS_JNI_1_2) {
		if ((srcData = (*env)->GetPrimitiveArrayCritical(env, jSrcData, NULL)) == NULL) goto fail;
		if ((alphaData = (*env)->GetPrimitiveArrayCritical(env, jAlphaData, NULL)) == NULL) goto fail;
	} else
#endif
	{
		if ((srcData = (*env)->GetByteArrayElements(env, jSrcData, NULL)) == NULL) goto fail;
		if ((alphaData = (*env)->GetByteArrayElements(env, jAlphaData, NULL)) == NULL) goto fail;
	}

	int apinc = imgWidth - srcWidth;
	int ap = srcY * imgWidth + srcX, sp = 0;

	//byte[] srcData = new byte[dibBM.bmWidthBytes * dibBM.bmHeight];
	//byte[] alphaData = srcImage.alphaData;
	int x, y;
	for (y = 0; y < srcHeight; ++y) {
		for (x = 0; x < srcWidth; ++x) {
			int alpha = alphaData[ap++] & 0xff;
			int r = ((srcData[sp + 0] & 0xFF) * alpha) + 128;
			r = (r + (r >> 8)) >> 8;
			int g = ((srcData[sp + 1] & 0xFF) * alpha) + 128;
			g = (g + (g >> 8)) >> 8;
			int b = ((srcData[sp + 2] & 0xFF) * alpha) + 128;
			b = (b + (b >> 8)) >> 8;
			srcData[sp+0] = (char)r;
			srcData[sp+1] = (char)g;
			srcData[sp+2] = (char)b;
			srcData[sp+3] = (char)alpha;
			sp += 4;
		}
		ap += apinc;
	}

fail:
	#ifdef JNI_VERSION_1_2
		if (IS_JNI_1_2) {
			if (srcData != NULL) (*env)->ReleasePrimitiveArrayCritical(env, jSrcData, srcData, 0);
			if (alphaData != NULL) (*env)->ReleasePrimitiveArrayCritical(env, jAlphaData, alphaData, 0);
		} else
	#endif
		{
			if (srcData != NULL) (*env)->ReleaseByteArrayElements(env, jSrcData, srcData, 0);
			if (alphaData != NULL) (*env)->ReleaseByteArrayElements(env, jAlphaData, alphaData, 0);
		}

}
