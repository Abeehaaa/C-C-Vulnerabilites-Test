#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *OPENAI_API_KEY = "sk-test_4a9f8b3d2c1e7f6a9b0c1d2e3f4a5b6c";
const char *AWS_SECRET_KEY = "wJalrXUtnFEMI/K7MDENG/bPxRfiCYFAKEEXAMPLEKEY123456";
const char *GITHUB_PAT     = "ghp_FAKE1234567890abcdef1234567890abcdef";

void write_line_stdout(const char *s){
    if (s) { fputs(s, stdout); }
    fputc('\n', stdout);
}

void mask_and_print(const char *label, const char *key) {
    size_t len = strlen(key);
    if (len <= 8) {
        fputs(label, stdout); fputs(": ", stdout);
        fputs(key, stdout); fputc('\n', stdout);
        return;
    }
    char buf[128];
    size_t show_front = 4, show_back = 4;
    if (len >= sizeof(buf)-1) {
        fputs(label, stdout); fputs(": (key too long)\n", stdout);
        return;
    }
    size_t pos = 0;
    for (size_t i = 0; i < show_front; ++i) buf[pos++] = key[i];
    size_t masked = (len > show_front + show_back) ? (len - show_front - show_back) : 0;
    for (size_t i = 0; i < masked; ++i) buf[pos++] = '*';
    for (size_t i = len - show_back; i < len; ++i) buf[pos++] = key[i];
    buf[pos] = '\0';

    fputs(label, stdout); fputs(": ", stdout);
    fputs(buf, stdout); fputc('\n', stdout);
}

int simulate_api_call(const char *service, const char *key) {
    if (!service || !key) return 1;
    if (strlen(key) < 10) return 2;

    fputs("Simulating request to ", stdout);
    fputs(service, stdout);
    fputs(" using provided key (not actually contacting server)...\n", stdout);

    fputs("Used key: ", stdout);
    mask_and_print("", key);  // label empty → just masked key + newline
    return 0;
}

int check_for_keyword(const char *haystack, const char *needle) {
    if (!haystack || !needle) return 0;
    return strstr(haystack, needle) != NULL;
}

void fputs_literal(FILE *fp, const char *s){
    if (s) fputs(s, fp);
}

int main(void) {
    write_line_stdout("=== Secrets Demo (for scanner testing) ===");
    fputc('\n', stdout);

    mask_and_print("OPENAI_API_KEY", OPENAI_API_KEY);
    mask_and_print("AWS_SECRET_KEY",  AWS_SECRET_KEY);
    mask_and_print("GITHUB_PAT",      GITHUB_PAT);

    write_line_stdout("");
    write_line_stdout("Running quick simulated API calls:");
    simulate_api_call("OpenAI", OPENAI_API_KEY);
    simulate_api_call("AWS",    AWS_SECRET_KEY);
    simulate_api_call("GitHub", GITHUB_PAT);

    write_line_stdout("");
    write_line_stdout("Simple pattern checks in source (simulation):");
    if (check_for_keyword(OPENAI_API_KEY, "sk-"))
        write_line_stdout("OpenAI key looks like an OpenAI-style key (prefix sk-)");
    if (check_for_keyword(GITHUB_PAT, "ghp_"))
        write_line_stdout("GitHub PAT looks like a GitHub-style token (prefix ghp_)");
    if (check_for_keyword(AWS_SECRET_KEY, "wJalr"))
        write_line_stdout("AWS secret key has typical AWS-like prefix");

    write_line_stdout("");
    write_line_stdout("Saving masked keys to a local file 'secrets_report.txt' (masked) ...");

    FILE *f = fopen("secrets_report.txt", "w");
    if (!f) {
        write_line_stdout("Could not write report file");
        return 1;
    }

    // OPENAI
    fputs_literal(f, "OPENAI_API_KEY: ");
    for (int i = 0; i < 4 && OPENAI_API_KEY[i]; ++i) fputc(OPENAI_API_KEY[i], f);
    fputs_literal(f, "****");
    size_t l = strlen(OPENAI_API_KEY);
    for (size_t i = (l>4?l-4:0); i < l; ++i) fputc(OPENAI_API_KEY[i], f);
    fputc('\n', f);

    // AWS
    fputs_literal(f, "AWS_SECRET_KEY: ");
    for (int i = 0; i < 4 && AWS_SECRET_KEY[i]; ++i) fputc(AWS_SECRET_KEY[i], f);
    fputs_literal(f, "****");
    l = strlen(AWS_SECRET_KEY);
    for (size_t i = (l>4?l-4:0); i < l; ++i) fputc(AWS_SECRET_KEY[i], f);
    fputc('\n', f);

    // GITHUB
    fputs_literal(f, "GITHUB_PAT: ");
    for (int i = 0; i < 4 && GITHUB_PAT[i]; ++i) fputc(GITHUB_PAT[i], f);
    fputs_literal(f, "****");
    l = strlen(GITHUB_PAT);
    for (size_t i = (l>4?l-4:0); i < l; ++i) fputc(GITHUB_PAT[i], f);
    fputc('\n', f);

    fclose(f);
    write_line_stdout("Report written. Scanner should detect the raw literals inside this source file.");
    return 0;
}
