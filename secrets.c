#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *OPENAI_API_KEY = "sk-test_4a9f8b3d2c1e7f6a9b0c1d2e3f4a5b6c";
const char *AWS_SECRET_KEY = "wJalrXUtnFEMI/K7MDENG/bPxRfiCYFAKEEXAMPLEKEY123456";
const char *GITHUB_PAT     = "ghp_FAKE1234567890abcdef1234567890abcdef";

void mask_and_print(const char *label, const char *key) {
    size_t len = strlen(key);
    if (len <= 8) {
        printf("%s: %s\n", label, key);
        return;
    }
    char buf[128];
    size_t show_front = 4;
    size_t show_back = 4;
    if (len >= sizeof(buf)-1) {
        printf("%s: (key too long)\n", label);
        return;
    }
    for (size_t i = 0; i < show_front; ++i) buf[i] = key[i];
    size_t pos = show_front;
    size_t masked = (len > show_front + show_back) ? (len - show_front - show_back) : 0;
    for (size_t i = 0; i < masked; ++i) buf[pos++] = '*';
    for (size_t i = len - show_back; i < len; ++i) buf[pos++] = key[i];
    buf[pos] = '\0';
    printf("%s: %s\n", label, buf);
}

int simulate_api_call(const char *service, const char *key) {
    if (!service || !key) return 1;
    if (strlen(key) < 10) return 2;
    printf("Simulating request to %s using provided key (not actually contacting server)...\n", service);
    mask_and_print("Used key", key);
    return 0;
}

int check_for_keyword(const char *haystack, const char *needle) {
    if (!haystack || !needle) return 0;
    return strstr(haystack, needle) != NULL;
}

int main(int argc, char **argv) {
    printf("=== Secrets Demo (for scanner testing) ===\n\n");

    mask_and_print("OPENAI_API_KEY", OPENAI_API_KEY);
    mask_and_print("AWS_SECRET_KEY", AWS_SECRET_KEY);
    mask_and_print("GITHUB_PAT", GITHUB_PAT);

    printf("\nRunning quick simulated API calls:\n");
    simulate_api_call("OpenAI", OPENAI_API_KEY);
    simulate_api_call("AWS", AWS_SECRET_KEY);
    simulate_api_call("GitHub", GITHUB_PAT);

    printf("\nSimple pattern checks in source (simulation):\n");
    if (check_for_keyword(OPENAI_API_KEY, "sk-")) printf("OpenAI key looks like an OpenAI-style key (prefix sk-)\n");
    if (check_for_keyword(GITHUB_PAT, "ghp_")) printf("GitHub PAT looks like a GitHub-style token (prefix ghp_)\n");
    if (check_for_keyword(AWS_SECRET_KEY, "wJalr")) printf("AWS secret key has typical AWS-like prefix\n");

    printf("\nSaving masked keys to a local file 'secrets_report.txt' (masked) ...\n");
    FILE *f = fopen("secrets_report.txt", "w");
    if (!f) {
        printf("Could not write report file\n");
        return 1;
    }
    fprintf(f, "OPENAI_API_KEY: ");
    for (int i = 0; i < 4 && OPENAI_API_KEY[i]; ++i) fputc(OPENAI_API_KEY[i], f);
    fprintf(f, "****");
    size_t l = strlen(OPENAI_API_KEY);
    for (size_t i = (l>4?l-4:0); i < l; ++i) fputc(OPENAI_API_KEY[i], f);
    fprintf(f, "\n");

    fprintf(f, "AWS_SECRET_KEY: ");
    for (int i = 0; i < 4 && AWS_SECRET_KEY[i]; ++i) fputc(AWS_SECRET_KEY[i], f);
    fprintf(f, "****");
    l = strlen(AWS_SECRET_KEY);
    for (size_t i = (l>4?l-4:0); i < l; ++i) fputc(AWS_SECRET_KEY[i], f);
    fprintf(f, "\n");

    fprintf(f, "GITHUB_PAT: ");
    for (int i = 0; i < 4 && GITHUB_PAT[i]; ++i) fputc(GITHUB_PAT[i], f);
    fprintf(f, "****");
    l = strlen(GITHUB_PAT);
    for (size_t i = (l>4?l-4:0); i < l; ++i) fputc(GITHUB_PAT[i], f);
    fprintf(f, "\n");

    fclose(f);
    printf("Report written. Scanner should detect the raw literals inside this source file.\n");
    return 0;
}
