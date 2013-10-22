#include "fileops.h"
	else if (GIT_PERMS_IS_EXEC(mode)) /* -V536 */
		git_buf_printf(out, "%c\t%s%c %s%c\n", code,
		git_buf_printf(out, "%c\t%s%c %s%c\n", code,
			delta->old_file.path, old_suffix, delta->new_file.path, new_suffix);
static int diff_print_oid_range(
	git_buf *out, const git_diff_delta *delta, int oid_strlen)
	git_oid_tostr(start_oid, oid_strlen, &delta->old_file.oid);
	git_oid_tostr(end_oid, oid_strlen, &delta->new_file.oid);
static int diff_delta_format_with_paths(
	git_buf *out,
	const git_diff_delta *delta,
	const char *oldpfx,
	const char *newpfx,
	const char *template)
	if (git_oid_iszero(&delta->old_file.oid)) {
		oldpfx = "";
		oldpath = "/dev/null";
	}
	if (git_oid_iszero(&delta->new_file.oid)) {
		newpfx = "";
		newpath = "/dev/null";
	}
	return git_buf_printf(out, template, oldpfx, oldpath, newpfx, newpath);
}
int git_diff_delta__format_file_header(
	git_buf *out,
	const git_diff_delta *delta,
	const char *oldpfx,
	const char *newpfx,
	int oid_strlen)
{
	if (!oid_strlen)
		oid_strlen = GIT_ABBREV_DEFAULT + 1;
	git_buf_clear(out);

	git_buf_printf(out, "diff --git %s%s %s%s\n",
	if (diff_print_oid_range(out, delta, oid_strlen) < 0)
	if ((delta->flags & GIT_DIFF_FLAG_BINARY) == 0)
		diff_delta_format_with_paths(
			out, delta, oldpfx, newpfx, "--- %s%s\n+++ %s%s\n");
	return git_buf_oom(out) ? -1 : 0;
}
static int diff_print_patch_file(
	const git_diff_delta *delta, float progress, void *data)
{
	diff_print_info *pi = data;
	const char *oldpfx =
		pi->diff ? pi->diff->opts.old_prefix : DIFF_OLD_PREFIX_DEFAULT;
	const char *newpfx =
		pi->diff ? pi->diff->opts.new_prefix : DIFF_NEW_PREFIX_DEFAULT;
	uint32_t opts_flags = pi->diff ? pi->diff->opts.flags : GIT_DIFF_NORMAL;

	GIT_UNUSED(progress);

	if (S_ISDIR(delta->new_file.mode) ||
		delta->status == GIT_DELTA_UNMODIFIED ||
		delta->status == GIT_DELTA_IGNORED ||
		(delta->status == GIT_DELTA_UNTRACKED &&
		 (opts_flags & GIT_DIFF_INCLUDE_UNTRACKED_CONTENT) == 0))
		return 0;

	if (git_diff_delta__format_file_header(
			pi->buf, delta, oldpfx, newpfx, pi->oid_strlen) < 0)

	if (diff_delta_format_with_paths(
			pi->buf, delta, oldpfx, newpfx,
			"Binary files %s%s and %s%s differ\n") < 0)
	if (git_buf_put(pi->buf, header, header_len) < 0)
	git_buf_grow(pi->buf, content_len + 2);
		git_buf_putc(pi->buf, line_origin);

	git_buf_put(pi->buf, content, content_len);