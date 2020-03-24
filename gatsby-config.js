module.exports = {
  siteMetadata: {
    title: "Blog",
    name: "Blog by Shun Kakinoki",
    siteUrl: "https://blog.shunkakinoki.com",
    description: "Personal Blog by Shun Kakinoki",
    hero: {
      heading: "My Journey Towards Obliterating the Galaxy.",
      maxWidth: 652,
    },
    social: [
      {
        name: "github",
        url: "https://github.com/shunkakinoki",
      },
    ],
    languages: ["en", "ja"],
  },
  plugins: [
    {
      resolve: "@narative/gatsby-theme-novela",
      options: {
        contentPosts: "content/posts",
        contentAuthors: "content/authors",
        basePath: "/",
        authorsPage: true,
        mailchimp: true,
        sources: {
          local: true,
        },
      },
    },
    {
      resolve: "gatsby-plugin-manifest",
      options: {
        name: "Novela by Narative",
        short_name: "Novela",
        start_url: "/",
        background_color: "#fff",
        theme_color: "#fff",
        display: "standalone",
        // icon: "src/assets/favicon.png",
      },
    },
    {
      resolve: "gatsby-plugin-i18n",
      options: {
        langKeyForNull: "ja",
        langKeyDefault: "ja",
        useLangKeyLayout: true,
        prefixDefault: true,
        pagesPaths: ["/content"],
      },
    },
    {
      resolve: "gatsby-plugin-google-analytics",
      options: {
        trackingId: "UA-134813374-5",
        anonymize: true,
      },
    },
    {
      resolve: "gatsby-plugin-mailchimp",
      options: {
        endpoint:
          "https://shunkakinoki.us4.list-manage.com/subscribe/post?u=12161f05e225d968a8366de58&amp;id=65c5673d05",
      },
    },
  ],
};
