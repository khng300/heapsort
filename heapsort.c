/*
 * Copyright 2017 Ka Ho Ng <khng300@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "heapsort.h"

/*
 * Swap two elements
 */
static inline void
elm_swap(TYPE_T *a, TYPE_T *b)
{
	TYPE_T tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * Push the last element of the array into the heap.
 */
void
heap_push(TYPE_T *base, size_t nelms, heapsort_cmp *cmp)
{
	size_t prev;	/* The index of the previous element */
	size_t cur;	/* The index of the current element */
	size_t parent;	/* The index of the parent element */

	cur = nelms - 1;	/* Start with the index of the last element */
	prev = cur;
	parent = (cur - 1) >> 1;	

	if (nelms < 2)
		/* Shortcut for situations that certainly do not need to do
		 * anything */
		return;

	while (cur) {
		int cmp_res;

		/*
		 * Compare the parent element and the current element.
		 * For sorting the array from the smallest element to the
		 * largest element we need to build a max-heap in-situ.
		 */
		cmp_res = cmp(base[cur], base[parent]);
		if (cmp_res < 0)
			break;

		/* Since the current element is larger than its parent, we
		 * sift it up by swapping it with its parent */
		elm_swap(base + cur, base + parent);

		prev = cur;
		cur = parent;
		parent = (cur - 1) >> 1;
	}
}

/*
 * Pop the first element from the heap, and throw it to the last slot of the
 * array. At the end the size of the heap will be reduced by one.
 */
static void
heap_pop(TYPE_T *base, size_t nelms, heapsort_cmp *cmp)
{
	size_t cur;	/* The index of the current element */
	size_t last;	/* The index of the last element */

	if (nelms < 2)
		/* Shortcut for situations that certainly do not need to do
		 * anything */
		return;

	cur = 0;		/* Start with the index of the first element */
	last = nelms - 1;

	/* Swap the first element (max) with the last element */
	elm_swap(base + cur, base + last);

	while (cur < last) {
		size_t left_child;	/* The index of the left child */
		size_t right_child;	/* The index of the right child */
		
		left_child = (cur << 1) + 1;
		right_child = (cur << 1) + 2;

		if (left_child < last && right_child < last) {
			size_t child;

			/*
			 * Both left child and right child exists
			 */
			child = cmp(base[left_child], base[right_child]) < 0
			    ? (right_child) : (left_child);

			if (cmp(base[cur], base[child]) < 0)
				elm_swap(base + cur, base + child);
			cur = child;
		} else if (left_child < last) {
			/*
			 * Only left child exists
			 */
			if (cmp(base[cur], base[left_child]) < 0)
				elm_swap(base + cur, base + last);
			cur = left_child;
		} else {
			/*
			 * This node has no children, do nothing
			 */
			break;
		}
	}
}

/*
 * This routine implements heapsort algorithm
 */
void
heapsort_s(TYPE_T *base, size_t nelms, heapsort_cmp *cmp)
{
	TYPE_T *first;
	TYPE_T *last;

	/* Shortcut for situations that certainly do not need sorting */
	if (nelms < 2)
		return;

	first = base;
	last = base;

	/*
	 * Construct a heap with minimal size first (in this case the array
	 * will be in its 
	 */
	while (last - first + 1 <= nelms) {
		heap_push(base, last - first + 1, cmp);
		last++;
	}

	/*
	 * Destroy the heap so that everything will be sorted
	 */
	while (--last - first + 1 > 1) {
		heap_pop(base, last - first + 1, cmp);
	}
}