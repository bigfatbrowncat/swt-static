/*******************************************************************************
 * Copyright (c) 2000, 2012 IBM Corporation and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    IBM Corporation - initial API and implementation
 *******************************************************************************/
package org.eclipse.swt.internal.cocoa;

public class NSOpenGLPixelFormat extends NSObject {

public NSOpenGLPixelFormat() {
	super();
}

public NSOpenGLPixelFormat(long /*int*/ id) {
	super(id);
}

public NSOpenGLPixelFormat(id id) {
	super(id);
}

public void getValues(long[] /*int[]*/ vals, int attrib, int screen) {
	OS.objc_msgSend(this.id, OS.sel_getValues_forAttribute_forVirtualScreen_, vals, attrib, screen);
}

public id initWithAttributes(int[] attribs) {
	long /*int*/ result = OS.objc_msgSend(this.id, OS.sel_initWithAttributes_, attribs);
	return result != 0 ? new id(result) : null;
}

}
