#include "report.h"
#include "memory_profiler.h"
#include "leak_detector.h"

void	mp_generate_report(void)
{
	t_leak_info	*leaks;

	if (!g_config.detect_leaks)
		return ;
	leaks = detect_leaks();
	if (!leaks)
		return ;
	if (g_config.format == REPORT_TEXT)
		generate_text_report(g_config.output_path);
	else if (g_config.format == REPORT_JSON)
		generate_json_report(g_config.output_path);
	else if (g_config.format == REPORT_CSV)
		generate_csv_report(g_config.output_path);
	print_leak_summary(leaks);
	free_leak_info(leaks);
}
