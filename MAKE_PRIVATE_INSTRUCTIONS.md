# How to Make This Repository Private

This repository is currently **public** on GitHub. To make it **private**, follow these steps:

## Method 1: Using GitHub Web Interface (Recommended)

1. Navigate to the repository settings:
   - Go to https://github.com/ShikiHTM/Danbooru_Crawler/settings

2. Scroll down to the **"Danger Zone"** section at the bottom of the settings page

3. Click on **"Change repository visibility"**

4. Select **"Make private"**

5. Confirm the change by:
   - Typing the repository name when prompted
   - Clicking the confirmation button

6. The repository will now be private and only visible to:
   - Repository owner
   - Explicitly added collaborators

## Method 2: Using GitHub CLI

If you have GitHub CLI (`gh`) installed:

```bash
gh repo edit ShikiHTM/Danbooru_Crawler --visibility private
```

## Method 3: Using GitHub API

Using curl with a personal access token:

```bash
curl -X PATCH \
  -H "Accept: application/vnd.github+json" \
  -H "Authorization: Bearer YOUR_PERSONAL_ACCESS_TOKEN" \
  https://api.github.com/repos/ShikiHTM/Danbooru_Crawler \
  -d '{"private":true}'
```

## What Happens When You Make a Repository Private?

- The repository will no longer be visible to the public
- Only you and collaborators you explicitly invite will have access
- GitHub Pages sites (if any) will be unpublished
- Fork will be detached if the parent repository is public
- Stars and watchers will be hidden from public view

## Important Notes

- **Permissions Required**: You must be the repository owner or have admin permissions to change visibility
- **GitHub Plans**: Private repositories are available on all GitHub plans (Free, Pro, Team, Enterprise)
- **Existing Clones**: Making a repository private does NOT affect existing clones that others may have made while it was public

## Alternative: Delete Sensitive Information

If you're making the repository private due to sensitive information being exposed, you should also:

1. Remove sensitive data from the repository history using tools like:
   - `git filter-repo`
   - `BFG Repo-Cleaner`

2. Rotate any exposed credentials, API keys, or tokens

3. Update `.gitignore` to prevent committing sensitive files in the future

---

**Note**: Repository visibility is a GitHub platform setting and cannot be changed through code modifications alone. This must be done by the repository owner through one of the methods above.
